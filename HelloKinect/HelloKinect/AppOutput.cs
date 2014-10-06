using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloKinect
{
    class AppOutput : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string _statusMessage;
        public string StatusMessage
        {
            get
            {
                return _statusMessage;
            }
            set
            {
                _statusMessage = value;
                OnPropertyChanged("StatusMessage");
            }
        }
        public AppOutput()
        {
            StatusMessage = "How dy";
        } 
        private void OnPropertyChanged(string property)
        {

            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(property));
        }
    }
}
