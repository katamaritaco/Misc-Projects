using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Hackathon
{
    class Question
    {
        public Texture2D question { get; set; }
        public Texture2D left_answer { get; set; }
        public LinkedList<Texture2D> left_duds { get; set; }
        public Texture2D right_answer { get; set; }

        public Question(String basename, ContentManager content)
        {
            this.question = content.Load<Texture2D>(basename + "q");
            this.left_answer = content.Load<Texture2D>(basename + "a");
            this.left_duds = new LinkedList<Texture2D>();
            for (int i = 1; i <= 3; i++)
            {
                this.left_duds.AddLast(content.Load<Texture2D>(basename + "d" + i));
            }
            this.right_answer = content.Load<Texture2D>(basename + "p");
        }
    }
}
