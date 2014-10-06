using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class moveToPoints : MonoBehaviour {
    Vector3 destination;// = new Vector3(0, 1, 15);
    Vector3 sphereDestination = new Vector3();
    string sphereString = "Sphere1";
    LinkedList<Vector3> route = new LinkedList<Vector3>();

    public float speed =  .3f;
    // Use this for initialization
    void Start()
    {


        //route = new LinkedList<Vector3>();
        /*
        route.AddLast(new Vector3(-0.888f, 1.08f, -0.338f));
        route.AddLast(new Vector3(0.124f, 1.08f, -0.161f));
        route.AddLast(new Vector3(0.984f, 1.08f, 0.344f));
        route.AddLast(new Vector3(0.984f, 1.08f, 1.861f));
        route.AddLast(new Vector3(-0.193f, 1.08f, 2.795f));
        route.AddLast(new Vector3(-3.411f, 1.08f, 2.875f));
        route.AddLast(new Vector3(-4.105f, 1.08f, 2.448f));
        route.AddLast(new Vector3(-3.758f, 1.08f, -1.610f));
        route.AddLast(new Vector3(-3.037f, 1.08f, -3.372f));
        route.AddLast(new Vector3(-1.658f, 1.08f, -3.675f));
        route.AddLast(new Vector3(1.268f, 1.08f, -3.708f));
        route.AddLast(new Vector3(3.892f, 1.08f, -2.464f));
        route.AddLast(new Vector3(4.027f, 1.08f, -1.623f));
        route.AddLast(new Vector3(5.010f, 1.08f, -1.182f));
        route.AddLast(new Vector3(5.790f, 1.08f, 1.328f));
        */


        for (int i = 1; i <= 22; i++)
        {
            sphereString = "Sphere" + i;
            GameObject sphere = GameObject.Find(sphereString);
            route.AddLast(sphere.transform.position);
        }
    }

    // Update is called once per frame
    void Update()
    {

        if (route.First != null)
        {
            destination = route.First.Value;
            if ((destination - gameObject.transform.position).magnitude < speed)
            {
                route.RemoveFirst();
            }

            //gameObject.transform.position = Vector3.MoveTowards(gameObject.transform.position, destination, speed);

            Vector3 moveTo = Vector3.MoveTowards(gameObject.transform.position, destination, speed);
            CharacterController cc = (CharacterController)gameObject.GetComponent("CharacterController");
            //cc.SimpleMove((moveTo - gameObject.transform.position) * 90);
            cc.Move(moveTo - gameObject.transform.position);
        }






        //GameObject sphere = GameObject.Find(sphereString);
       // destination = sphere.transform.position;
        //gameObject.transform.position = Vector3.MoveTowards(transform.position, destination, speed * Time.deltaTime);
    }

    void OnGUI()
    {
        GUI.Label(new Rect(280.0f, 180.0f, 200.0f, 20.0f), "destination position");
        GUI.Label(new Rect(280.0f, 200.0f, 200.0f, 20.0f), destination.ToString("F3"));
        GUI.Label(new Rect(280.0f, 240.0f, 200.0f, 20.0f), transform.position.ToString("F3"));
        GUI.Label(new Rect(280.0f, 220.0f, 200.0f, 20.0f), "current position");
    }
}
