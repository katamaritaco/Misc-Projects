using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using Kinect.Toolbox;
using Kinect.Toolbox.Voice;
using Microsoft.Kinect;
using Kinect.Toolbox.Record;
using System.Timers;
using Microsoft.Kinect.Toolkit;
using Microsoft.Kinect.Toolkit.Controls;


namespace HelloKinect
{
    /// <summary>
    /// Interaction logic for SelectionWindow.xaml
    /// </summary>
    public partial class SelectionWindow : Window
    {
        public KinectSensor kinectSensor;
        private KinectSensorChooser sensorChooser;
        private Skeleton[] skeletons;
        readonly ColorStreamManager colorManager = new ColorStreamManager();
        readonly DepthStreamManager depthManager = new DepthStreamManager();
        bool displayDepth = false;
        GestureIO fileManager;
        List<CoordinateContainer> left_coordinates = new List<CoordinateContainer>();
        List<CoordinateContainer> right_coordinates = new List<CoordinateContainer>();

        List<string> keywordList = new List<string>();
        List<string> operatorList = new List<string>();
        List<string> functionList = new List<string>();
        List<string> variableList = new List<string>();

        public string selectedToken = "";

        public SelectionWindow()
        {
            InitializeComponent();
            PopulateLists();
        }

        /**
         * This is the function to check whether Kinect is unpluged or not
         * 
         * */
        void Kinects_StatusChanged(object sender, StatusChangedEventArgs e)
        {
            switch (e.Status)
            {
                case KinectStatus.Connected:
                    if (kinectSensor == null)
                    {
                        kinectSensor = e.Sensor;
                        Initialize();
                    }
                    break;
                case KinectStatus.Disconnected:
                    if (kinectSensor == e.Sensor)
                    {
                        Clean();
                        MessageBox.Show("Kinect was disconnected");
                    }
                    break;
                case KinectStatus.NotReady:
                    break;
                case KinectStatus.NotPowered:
                    if (kinectSensor == e.Sensor)
                    {
                        Clean();
                        MessageBox.Show("Kinect is not powered");
                    }
                    break;
                default:
                    MessageBox.Show("Unhandled Status: " + e.Status);
                    break;
            }
            
        }

        /*
         * This is been called from MainWindow.xaml
         */
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.sensorChooser = new KinectSensorChooser();
            this.sensorChooser.KinectChanged += SensorChooserOnKinectChanged;
            this.sensorChooserUi.KinectSensorChooser = this.sensorChooser;
            this.sensorChooser.Start();

            try
            {
                //listen to any status change for Kinects
                KinectSensor.KinectSensors.StatusChanged += Kinects_StatusChanged;

                //loop through all the Kinects attached to this PC, and start the first that is connected without an error.
                foreach (KinectSensor kinect in KinectSensor.KinectSensors)
                {
                    if (kinect.Status == KinectStatus.Connected)
                    {
                        kinectSensor = kinect;
                        break;
                    }
                }
                if (KinectSensor.KinectSensors.Count == 0)
                    MessageBox.Show("No Kinect found");
                else
                    Initialize();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /*
         * This function is been called from MainWindow.xaml
         */
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Clean();
        }

        /*
         * Get everything initialized
         */
        public void Initialize() {
            if (kinectSensor == null)
                return;

            //kinectSensor.ColorStream.Enable(ColorImageFormat.RgbResolution640x480Fps30);
            //kinectSensor.ColorFrameReady += kinectRuntime_ColorFrameReady;

            //kinectSensor.DepthStream.Enable(DepthImageFormat.Resolution320x240Fps30);
            //kinectSensor.DepthFrameReady += kinectSensor_DepthFrameReady;

            kinectSensor.SkeletonStream.Enable(new TransformSmoothParameters
            {
                Smoothing = 0.5f,
                Correction = 0.5f,
                Prediction = 0.5f,
                JitterRadius = 0.05f,
                MaxDeviationRadius = 0.04f
            });

            kinectSensor.SkeletonFrameReady += kinectRuntime_SkeletonFrameReady;

            //Add keywords that you wan to detect
            //v_commander = new VoiceCommander("record", "stop", "fly away", "flapping", "start", "finish", "write");

            kinectSensor.Start();
            //kinectDisplay.DataContext = colorManager;

            //v_commander.OrderDetected += voiceCommander_OrderDetected;
            //StartVoiceCommander();

            fileManager = new GestureIO();
            fileManager.loadGesture();
        }

        public void Clean() {
            //v_commander.OrderDetected -= voiceCommander_OrderDetected;
            if (kinectSensor != null)
            {
                //kinectSensor.DepthFrameReady -= kinectSensor_DepthFrameReady;
                //kinectSensor.ColorFrameReady -= kinectRuntime_ColorFrameReady;
                kinectSensor.SkeletonFrameReady -= kinectRuntime_SkeletonFrameReady;
                kinectSensor.Stop();
                kinectSensor = null;
            }
        }


        void kinectRuntime_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {

            using (SkeletonFrame frame = e.OpenSkeletonFrame())
            {
                if (frame == null)
                    return;

                frame.GetSkeletons(ref skeletons);

                if (skeletons.All(s => s.TrackingState == SkeletonTrackingState.NotTracked))
                    return;
            }
        }

        void kinectSensor_DepthFrameReady(object sender, DepthImageFrameReadyEventArgs e)
        {

            using (var frame = e.OpenDepthImageFrame())
            {
                if (frame == null)
                    return;

                if (!displayDepth)
                    return;

                depthManager.Update(frame);
            }
        }

        void kinectRuntime_ColorFrameReady(object sender, ColorImageFrameReadyEventArgs e)
        {

            using (var frame = e.OpenColorImageFrame())
            {
                if (frame == null)
                    return;


                if (displayDepth)
                    return;

                colorManager.Update(frame);
            }
        }

        private void SensorChooserOnKinectChanged(object sender, KinectChangedEventArgs args)
        {
            bool error = false;
            if (args.OldSensor != null)
            {
                try
                {
                    args.OldSensor.DepthStream.Range = DepthRange.Default;
                    args.OldSensor.SkeletonStream.EnableTrackingInNearRange = false;
                    args.OldSensor.DepthStream.Disable();
                    args.OldSensor.SkeletonStream.Disable();
                }
                catch (InvalidOperationException)
                {
                    // KinectSensor might enter an invalid state while enabling/disabling streams or stream features.
                    // E.g.: sensor might be abruptly unplugged.
                    error = true;
                }
            }

            if (args.NewSensor != null)
            {
                try
                {
                    args.NewSensor.DepthStream.Enable(DepthImageFormat.Resolution640x480Fps30);
                    args.NewSensor.SkeletonStream.Enable();

                    try
                    {
                        args.NewSensor.DepthStream.Range = DepthRange.Near;
                        args.NewSensor.SkeletonStream.EnableTrackingInNearRange = true;
                        args.NewSensor.SkeletonStream.TrackingMode = SkeletonTrackingMode.Seated;
                    }
                    catch (InvalidOperationException)
                    {
                        // Non Kinect for Windows devices do not support Near mode, so reset back to default mode.
                        args.NewSensor.DepthStream.Range = DepthRange.Default;
                        args.NewSensor.SkeletonStream.EnableTrackingInNearRange = false;
                        //error = true;
                    }
                }
                catch (InvalidOperationException)
                {
                    error = true;
                    // KinectSensor might enter an invalid state while enabling/disabling streams or stream features.
                    // E.g.: sensor might be abruptly unplugged.
                }
            }

            if (!error)
                kinectRegion.KinectSensor = args.NewSensor;
        }


        //We recreate the list each time we click one of the buttons.
        //This could have been done a lot better, but #hackcity
        void ButtonOnClick(Object sender, RoutedEventArgs e)
        {
            KinectCircleButton btn = (KinectCircleButton)sender;
            if (btn.Label.ToString() == "Keywords")
            {
                for (var i = 0; i < keywordList.Count; i++)
                {
                    KinectTileButton button = new KinectTileButton
                    {
                        //Name = keywordList.ElementAt(i) + "Button",
                        Content = keywordList.ElementAt(i),
                        ClickMode = System.Windows.Controls.ClickMode.Release,
                        Margin = new Thickness(0, 20, 60, 20),
                        //Background = new SolidColorBrush( Color.FromArgb(255,255,139,0) ),
                        Foreground = new SolidColorBrush(Color.FromArgb(255, 255, 255, 255))
                    };
                    button.Click += new RoutedEventHandler(OnScrollViewButtonClick);

                    keywordDefs.Children.Add(button);
                }
                keywordButton.IsEnabled = false;
                operatorButton.IsEnabled = true;
                functionButton.IsEnabled = true;
                variableButton.IsEnabled = true;

                operatorDefs.Children.Clear();
                functionDefs.Children.Clear();
                variableDefs.Children.Clear();
            }
            else if (btn.Label.ToString() == "Operators")
            {
                for (var i = 0; i < operatorList.Count; i++)
                {
                    KinectTileButton button = new KinectTileButton
                    {
                        //Name = operatorList.ElementAt(i) + "Button",
                        Content = operatorList.ElementAt(i),
                        ClickMode = System.Windows.Controls.ClickMode.Release,
                        Margin = new Thickness(0, 20, 60, 20),
                        //Background = new SolidColorBrush( Color.FromArgb(255,255,139,0) ),
                        Foreground = new SolidColorBrush(Color.FromArgb(255, 255, 255, 255))
                    };
                    button.Click += new RoutedEventHandler(OnScrollViewButtonClick);

                    operatorDefs.Children.Add(button);
                }
                keywordButton.IsEnabled = true;
                operatorButton.IsEnabled = false;
                functionButton.IsEnabled = true;
                variableButton.IsEnabled = true;

                variableDefs.Children.Clear();
                functionDefs.Children.Clear();
                keywordDefs.Children.Clear();
            }
            else if (btn.Label.ToString() == "Functions")
            {
                for (var i = 0; i < functionList.Count; i++)
                {
                    KinectTileButton button = new KinectTileButton
                    {
                        //Name = functionList.ElementAt(i) + "Button",
                        Content = functionList.ElementAt(i),
                        ClickMode = System.Windows.Controls.ClickMode.Release,
                        Margin = new Thickness(0, 20, 60, 20),
                        //Background = new SolidColorBrush( Color.FromArgb(255,255,139,0) ),
                        Foreground = new SolidColorBrush(Color.FromArgb(255, 255, 255, 255))
                    };
                    button.Click += new RoutedEventHandler(OnScrollViewButtonClick);

                    functionDefs.Children.Add(button);
                }
                keywordButton.IsEnabled = true;
                operatorButton.IsEnabled = true;
                functionButton.IsEnabled = false;
                variableButton.IsEnabled = true;

                operatorDefs.Children.Clear();
                variableDefs.Children.Clear();
                keywordDefs.Children.Clear();
            }
            else if (btn.Label.ToString() == "Variables")
            {
                for (var i = 0; i < variableList.Count; i++)
                {
                    KinectTileButton button = new KinectTileButton
                    {
                        //Name = variableList.ElementAt(i) + "Button",
                        Content = variableList.ElementAt(i),
                        ClickMode = System.Windows.Controls.ClickMode.Release,
                        Margin = new Thickness(0, 20, 60, 20),
                        //Background = new SolidColorBrush( Color.FromArgb(255,255,139,0) ),
                        Foreground = new SolidColorBrush(Color.FromArgb(255, 255, 255, 255))
                    };
                    button.Click += new RoutedEventHandler(OnScrollViewButtonClick);

                    variableDefs.Children.Add(button);

                }
                keywordButton.IsEnabled = true;
                operatorButton.IsEnabled = true;
                functionButton.IsEnabled = true;
                variableButton.IsEnabled = false;
                
                operatorDefs.Children.Clear();
                functionDefs.Children.Clear();
                keywordDefs.Children.Clear();
            }
            else if (btn.Label.ToString() == "Cancel")
            {
                MainWindow main = new MainWindow();
                Clean();
                this.Close();
                main.Show();
            }

        }
        

        void OnScrollViewButtonClick(Object sender, RoutedEventArgs e)
        {
            KinectTileButton btn = (KinectTileButton)sender;
            selectedToken = btn.Content.ToString();
            Console.WriteLine(selectedToken);
            //Back to the main windows
            MainWindow main = new MainWindow();
            GesturePackage pk = new GesturePackage(selectedToken);
            pk.setLeftCoordinates(left_coordinates);
            pk.setRightCoordinates(right_coordinates);
            Clean();
            this.Close();
            main.OpenMain(pk);
        }

        public void OpenWindow(List<CoordinateContainer> corL, List<CoordinateContainer> corR){
            left_coordinates = corL;
            right_coordinates = corR;
            this.Show();
        }

        void PopulateLists(){
            keywordList.Add("def");
            keywordList.Add("if");
            keywordList.Add("elif");
            keywordList.Add("else");
            keywordList.Add("return");

            operatorList.Add("==");
            operatorList.Add("=");
            operatorList.Add("+");
            operatorList.Add("-");

            functionList.Add("WRITEDONTNEEDS?");
            functionList.Add("print");

            variableList.Add("functionDecl1");
            variableList.Add("functionDecl2");
            variableList.Add("functionDecl3");
            variableList.Add("variable1");
            variableList.Add("variable2");
            variableList.Add("variable3");
            variableList.Add("variable4");
            variableList.Add("variable5");
            variableList.Add("1");
        }

    }
}
