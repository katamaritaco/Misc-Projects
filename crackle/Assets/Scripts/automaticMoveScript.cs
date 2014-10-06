using UnityEngine;
using System.Collections;

public class automaticMoveScript : MonoBehaviour {
    Vector3 destination = new Vector3(0,1,15);
    public float speed = 1;
	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
        transform.position = Vector3.MoveTowards(transform.position, destination, speed * Time.deltaTime);
	}

}
