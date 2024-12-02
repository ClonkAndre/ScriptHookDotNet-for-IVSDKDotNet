using System;

using GTA;
using GTA.Native;

namespace DebugTest
{
    public class Main : Script
    {

        public Main()
        {
            Tick += Main_Tick;
        }

        private void Main_Tick(object sender, EventArgs e)
        {
            Vector3 v = Game.LocalPlayer.Character.Position;
            Function.Call("DRAW_CHECKPOINT", v.X, v.Y, v.Z, 1f, 255, 255, 255);

            //GTA.Object[] objects = World.GetAllObjects();
            //Game.DisplayText("objects length: " + objects.Length.ToString());
            //for (int i = 0; i < objects.Length; i++)
            //{
            //    GTA.Object obj = objects[i];
            //    Function.Call("DRAW_CHECKPOINT", obj.Position.X, obj.Position.Y, obj.Position.Z, 1f, 255, 255, 255);
            //}
        }

    }
}
