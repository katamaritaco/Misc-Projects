using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;


namespace Hackathon
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Texture2D sushiSensei;
        Texture2D sushiSensei2;
        Texture2D sushiSensei3;
        Texture2D sushiSensei4;
        Texture2D sushiSensei5;
        Texture2D leftSlap;
        Texture2D rightSlap;
        Texture2D leftTable;
        Texture2D rightTable;
        Texture2D actionBox;
        Texture2D background;
        Texture2D cursor;
        Texture2D plate;
        Texture2D scoreboard;
        Texture2D logo;
        Texture2D line;
        SpriteFont font;
        Boolean leftStop = false;
        Boolean rightStop = false;
        
        int currentScore = 0;
        Boolean winning = false;
        Boolean gameEnd = false;

        Texture2D question, left_correct, right_correct;
        List<Texture2D> left_answers;
        List<Texture2D> right_answers;

        Plate[] AllPlates = { new Plate(220, 30, -0.75, 2.25, 30, 220, null), 
                              new Plate(265, -120, -0.75, 2.25, 30, 220, null), 
                              new Plate(315, -270, -0.75, 2.25, 30, 220, null), 
                              new Plate(370, -420, -0.75, 2.25, 30, 220, null), 

                              new Plate(540, 30, 0.4, 2.25, 30, 540, null), 
                              new Plate(520, -120, 0.4, 2.25, 30, 540, null), 
                              new Plate(500, -270, 0.4, 2.25, 30, 540, null), 
                              new Plate(480, -420, 0.4, 2.25, 30, 540, null) };

        public enum GameStates
        {
            Menu,
            Running,
            End
        }

        public static GameStates gamestate;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            graphics.PreferredBackBufferWidth = 800;
            graphics.PreferredBackBufferHeight = 600;
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here

            gamestate = GameStates.Menu;

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            sushiSensei = this.Content.Load<Texture2D>("Images/chinaman");
            sushiSensei2 = this.Content.Load<Texture2D>("Images/chinaman2");
            sushiSensei3 = this.Content.Load<Texture2D>("Images/chinaman3");
            sushiSensei4 = this.Content.Load<Texture2D>("Images/chinaman4");
            sushiSensei5 = this.Content.Load<Texture2D>("Images/chinaman5");
            leftSlap = this.Content.Load<Texture2D>("Images/left_slap");
            rightSlap = this.Content.Load<Texture2D>("Images/right_slap");
            leftTable = this.Content.Load<Texture2D>("Images/leftTable");
            rightTable = this.Content.Load<Texture2D>("Images/rightTable");
            actionBox = this.Content.Load<Texture2D>("Images/actionBox");
            background = this.Content.Load<Texture2D>("Images/background");
            cursor = this.Content.Load<Texture2D>("Images/cursor");
            plate = this.Content.Load<Texture2D>("Images/plate");
            line = this.Content.Load<Texture2D>("Images/line");
            scoreboard = this.Content.Load<Texture2D>("Images/scoreboard");
            logo = this.Content.Load<Texture2D>("Images/logo");
            Song song = Content.Load<Song>("japanmusic");  // Put the name of your song in instead of "song_title"
            //SoundEffect hiya = Content.Load<SoundEffect>("hiya");
            MediaPlayer.Play(song);

            font = this.Content.Load<SpriteFont>("Images/SpriteFont1");
            loadJapanese();
            loadPlates();
        }

        private void loadSpanish()
        {
            allQuestions = new List<Question>();
            questionsToAsk = new List<Question>();
            for (int i = 1; i <= 5; i++)
            {
                Question q = new Question("Spanish/q" + i, this.Content);
                allQuestions.Add(q);
                questionsToAsk.Add(q);
            }
            this.shuffle<Question>(questionsToAsk);
        }

        private void loadJapanese()
        {
            allQuestions = new List<Question>();
            questionsToAsk = new List<Question>();
            for (int i = 1; i <= 11; i++)
            {
                Question q = new Question("Japanese/q" + i, this.Content);
                allQuestions.Add(q);
                questionsToAsk.Add(q);
            }
            this.shuffle<Question>(questionsToAsk);
        }

        private void loadGerman()
        {
            allQuestions = new List<Question>();
            questionsToAsk = new List<Question>();
            for (int i = 1; i <= 5; i++)
            {
                Question q = new Question("German/q" + i, this.Content);
                allQuestions.Add(q);
                questionsToAsk.Add(q);
            }
            this.shuffle<Question>(questionsToAsk);
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // Unload any non ContentManager content here
        }

        private bool newPress(Keys key)
        {
            if (firstFrame)
                return false;
            return lastKeys.IsKeyUp(key) && thisKeys.IsKeyDown(key);
        }

        private List<Question> allQuestions;
        private List<Question> questionsToAsk;

        // Loads a new question from the questionsToAsk onto the plates.
        private void loadPlates()
        {
            if (questionsToAsk.Count == 0)
            {
                leftStop = true;
                rightStop = true;
                gameEnd = true;
                return;
            }
            Question asking = questionsToAsk[questionsToAsk.Count - 1];
            questionsToAsk.RemoveAt(questionsToAsk.Count - 1);

            question = asking.question;
            left_correct = asking.left_answer;
            right_correct = asking.right_answer;

            // Take the correct answer and the three duds, and assign them randomly to left plates
            left_answers = new List<Texture2D>();
            left_answers.Add(asking.left_answer);
            foreach (Texture2D tex in asking.left_duds)
                left_answers.Add(tex);
            this.shuffle<Texture2D>(left_answers);
            for (int i = 0; i < 4; i++)
                AllPlates[i].plateContents = left_answers[i];

            // Take four random right answers (from all questions) and assign randomly to right plates
            right_answers = new List<Texture2D>();
            List<int> indexes = new List<int>();
            for (int i = 0; i < allQuestions.Count; i++)
                indexes.Add(i);
            this.shuffle<int>(indexes);
            for (int i = 0; i < 4; i++)
                AllPlates[i + 4].plateContents = allQuestions[indexes[i]].right_answer;
            // hack to make sure the correct right_answer is actually in there
            bool b = false;
            for (int i = 0; i < 4; i++)
                b = b || (allQuestions[indexes[i]].right_answer == asking.right_answer);
            if (!b)
            {
                Random rng = new Random();
                AllPlates[rng.Next(4) + 4].plateContents = asking.right_answer;
            }
        }

        private void shuffle<T>(IList<T> list)
        {
            Random rng = new Random();
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            lastKeys = thisKeys;
            thisKeys = Keyboard.GetState();
            thisMouse = Mouse.GetState();

            if (this.newPress(Keys.Right))
                rightStop = !rightStop;
            if (this.newPress(Keys.Left))
                leftStop = !leftStop;

            for (int i = 0; i < AllPlates.Length; i++)
            {
                if ((!leftStop && (i < 4)) || (!rightStop && (i >= 4)))
                {
                    bool slidingBefore = slidingPlates > 0;
                    slidingPlates = AllPlates[i].updatePlate(slidingPlates);
                    bool slidingAfter = slidingPlates > 0;
                    if (slidingBefore && !slidingAfter)
                    {
                        loadPlates();
                    }
                }
            }

            mouse_x = thisMouse.X;
            mouse_y = thisMouse.Y;
            mouse_down = thisMouse.LeftButton == ButtonState.Pressed;

            firstFrame = false;

            if (leftStop && rightStop && !gameEnd)
            {
                winning = this.isCorrect();
                if (winning)
                {
                    currentScore += 200;
                    slidingPlates = 8;
                    madFace = 0;
                    leftStop = false;
                    rightStop = false;
                }
                else
                {
                    currentScore -= 100;
                    madFace++;
                    leftStop = false;
                    rightStop = false;
                }
            }

            winning = this.isCorrect() && leftStop && rightStop;
            if (winning) currentScore += 200;

            base.Update(gameTime);
        }

        int slidingPlates = 0;
        int madFace = 0;

        private int mod(int x, int m)
        {
            return (x % m + m) % m;
        }

        private bool isCorrect()
        {
            bool gotLeft = false;
            bool gotRight = false;
            for (int i = 0; i <= 3; i++)
            {
                Plate p = AllPlates[i];
                if (p.in_zone && p.plateContents == left_correct)
                    gotLeft = true;
            }
            for (int i = 4; i <= 7; i++)
            {
                Plate p = AllPlates[i];
                if (p.in_zone && p.plateContents == right_correct)
                    gotRight = true;
            }
            return gotLeft && gotRight;
        }

        bool firstFrame = true;
        MouseState thisMouse;
        KeyboardState lastKeys;
        KeyboardState thisKeys;

        int mouse_x, mouse_y;
        bool mouse_down;

        private void drawCenter(Texture2D tex, Vector2 centerAt, Color color)
        {
            Vector2 centerPoint = new Vector2(tex.Width / 2, tex.Height / 2);
            spriteBatch.Draw(tex, Vector2.Add(centerAt, Vector2.Negate(centerPoint)), color);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            SoundEffect hiya = this.Content.Load<SoundEffect>("hiya");
            SoundEffect correct = this.Content.Load<SoundEffect>("correct");
            SoundEffect washing = this.Content.Load<SoundEffect>("washing");
            GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();
            spriteBatch.Draw(background, Vector2.Zero, Color.Wheat);
            if (slidingPlates > 0)
            {
                drawCenter(sushiSensei4, new Vector2(430, 250), Color.White);
                if (newPress(Keys.Left) || newPress(Keys.Right))
                {
                    correct.Play();
                }
            }
            else if (madFace == 0)
            {
                drawCenter(sushiSensei, new Vector2(430, 250), Color.White);
            }
            else if (madFace == 1)
            {
                drawCenter(sushiSensei2, new Vector2(430, 250), Color.White);
            }
            else if (madFace == 2)
            {
                drawCenter(sushiSensei3, new Vector2(430, 250), Color.White);
            }
            else
            {
                drawCenter(sushiSensei5, new Vector2(430, 250), Color.White);
            }

            if (leftStop)
            {
                drawCenter(leftSlap, new Vector2(430, 250), Color.White);
                if (newPress(Keys.Left))
                {
                    hiya.Play();
                }
            }

            if (rightStop)
            {
                drawCenter(rightSlap, new Vector2(430, 250), Color.White);
                if (newPress(Keys.Right))
                {
                    washing.Play();
                }
            }
            if (!gameEnd)
            {
                drawCenter(logo, new Vector2(400, 80), Color.White);
            }
            else
            {
                drawCenter(logo, new Vector2(400, 300), Color.White);
            }
            for (int i = 0; i < AllPlates.Length; i++)
            {
                double scale_factor = (((float)AllPlates[i].y_value + 170) / (670));
                spriteBatch.Draw(plate, new Vector2((int)Math.Ceiling(AllPlates[i].x_value), (int)Math.Ceiling(AllPlates[i].y_value - 100)), null, AllPlates[i].plateColor, 0f, Vector2.Zero, new Vector2((((float)AllPlates[i].y_value + 170) / (670)), (((float)AllPlates[i].y_value + 170) / (670))), SpriteEffects.None, 0f);
                spriteBatch.Draw(AllPlates[i].plateContents, new Vector2((int)Math.Ceiling(AllPlates[i].x_value + (150 * scale_factor - (1.25 * AllPlates[i].plateContents.Width * (scale_factor)))), (int)Math.Ceiling(AllPlates[i].y_value - 100)), null, AllPlates[i].plateColor, 0f, Vector2.Zero, new Vector2((((float)AllPlates[i].y_value + 170) / (670)), (((float)AllPlates[i].y_value + 170) / (670))), SpriteEffects.None, 0f);
            }

            spriteBatch.Draw(question, new Vector2(270, 125), Color.White);

            spriteBatch.Draw(scoreboard, new Vector2(310, 15), Color.White);
            spriteBatch.DrawString(font, "Score: " + currentScore, new Vector2(313, 15), Color.MintCream);
            spriteBatch.Draw(cursor, new Vector2(mouse_x, mouse_y), mouse_down ? Color.Red : Color.White);
            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
