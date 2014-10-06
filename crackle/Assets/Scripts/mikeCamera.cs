using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class mikeCamera : MonoBehaviour {

  float speed = 0.03f;
  LinkedList<Vector3> route;
  Vector3 display = new Vector3(0,0,0);

  // Use this for initialization
  void Start () {
    route = new LinkedList<Vector3>();
    route.AddLast (new Vector3(-0.888f, 1.08f, -0.338f));
    route.AddLast (new Vector3( 0.124f, 1.08f, -0.161f));
    route.AddLast (new Vector3( 0.984f, 1.08f,  0.344f));
    route.AddLast (new Vector3( 0.984f, 1.08f,  1.861f));
    route.AddLast (new Vector3(-0.193f, 1.08f,  2.795f));
    route.AddLast (new Vector3(-3.411f, 1.08f,  2.875f));
    route.AddLast (new Vector3(-4.105f, 1.08f,  2.448f));
    route.AddLast (new Vector3(-3.758f, 1.08f, -1.610f));
    route.AddLast (new Vector3(-3.037f, 1.08f, -3.372f));
    route.AddLast (new Vector3(-1.658f, 1.08f, -3.675f));
    route.AddLast (new Vector3( 1.268f, 1.08f, -3.708f));
    route.AddLast (new Vector3( 3.892f, 1.08f, -2.464f));
    route.AddLast (new Vector3( 4.027f, 1.08f, -1.623f));
    route.AddLast (new Vector3( 5.010f, 1.08f, -1.182f));
    route.AddLast (new Vector3( 5.790f, 1.08f,  1.328f));
  }
  
  // Update is called once per frame
  void Update () {
    if (route.First != null)
    {
      Vector3 destination = route.First.Value;
      if ((destination - gameObject.transform.position).magnitude < speed)
      {
        route.RemoveFirst();
      }

      //gameObject.transform.position = Vector3.MoveTowards(gameObject.transform.position, destination, speed);

      Vector3 moveTo = Vector3.MoveTowards(gameObject.transform.position, destination, speed);
      CharacterController cc = (CharacterController)gameObject.GetComponent("CharacterController");
      cc.SimpleMove((moveTo - gameObject.transform.position) * 90);
    }
    Vector3 euler = gameObject.transform.eulerAngles;
    euler.x = euler.x + -2.2f * Input.GetAxis("Mouse Y");
    if (euler.x > 70)
    {
      if (euler.x < 180)
      {
        euler.x = 70;
      }
      else
      {
        if (euler.x < 325)
        {
          euler.x = 325;
        }
      }
    }
    euler.y = (euler.y + 3 * Input.GetAxis("Mouse X")) % 360;
    euler.z = 0f;
    gameObject.transform.eulerAngles = euler;
  }

  void OnGUI()
  {
    // Vector3 dest = route.First.Value;
    // Vector3 here = gameObject.transform.position;
    // GUI.Label(new Rect(0,  0, 1000, 100), dest.ToString("F4"));
    // GUI.Label(new Rect(0, 25, 1000, 100), here.ToString("F4"));
    // GUI.Label(new Rect(0, 50, 1000, 100), (dest - here).ToString("F4"));
    // GUI.Label(new Rect(0, 75, 1000, 100), Vector3.ClampMagnitude(dest - here, speed).ToString("F4"));
    GUI.Label(new Rect(0,  0, 1000, 100), display.ToString("F4"));
  }
}
