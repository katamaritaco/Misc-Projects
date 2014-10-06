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
    public class Plate : Microsoft.Xna.Framework.Game
    {
        public Plate(double xOrigin, double yOrigin, double xSpeed, double ySpeed, double yReset, double xReset, Texture2D contents)
        {
            plateColor = Color.White;
            in_zone = false;
            y_reset = yReset;
            x_reset = xReset;
            x_value = xOrigin;
            y_value = yOrigin;
            x_speed = xSpeed;
            y_speed = ySpeed;
            x_origin = xOrigin;
            y_origin = yOrigin;
            plateContents = contents;
        }
        public bool in_zone { get; set; }
        public Color plateColor { get; set; }
        public double x_value { get; set; }
        public double y_value { get; set; }
        public double x_speed { get; set; }
        public double y_speed { get; set; }
        public double x_origin { get; set; }
        public double y_origin { get; set; }
        public double y_reset { get; set; }
        public double x_reset { get; set; }
        public Texture2D plateContents { get; set; }
        public bool finishedSliding { get; set; }

        public void origin()
        {
            this.x_value = this.x_origin;
            this.y_value = this.y_origin;
            this.finishedSliding = false;
        }

        public void reset()
        {
            this.x_value = this.x_reset;
            this.y_value = this.y_reset;
            this.finishedSliding = false;
        }

        // Takes the value of slidingPlates from Game1, and returns a new value for it.
        public int updatePlate(int slidingPlates)
        {
            bool sliding = slidingPlates != 0;
            this.x_value += (sliding ? 4 : 1) * this.x_speed;
            this.y_value += (sliding ? 4 : 1) * this.y_speed;
            if (this.y_value >= 650)
            {
                if (sliding)
                {
                    if (!finishedSliding)
                        slidingPlates -= 1;
                    finishedSliding = true;
                }
                else
                {
                    if (finishedSliding)
                        this.origin();
                    else
                        this.reset();
                }
            }
                

            this.in_zone = 450 <= this.y_value && this.y_value < 575;

            if (this.y_value >= 575) // fading out
            {
                int colorVal = (int)(255 - ((this.y_value - 575) / 50) * 255);
                this.plateColor = new Color(colorVal, colorVal, colorVal, colorVal);
            }
            else if (this.y_value >= 450) // in zone
            {
                this.plateColor = Color.Yellow;
            }
            else // on track
            {
                this.plateColor = Color.White;
            }

            return slidingPlates;
        }
    }
}