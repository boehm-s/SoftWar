extern crate zmq;

use std::thread;
use std::io::{self, BufRead};

fn main() {
    // create the ctx and the socket
    let ctx = zmq::Context::new();
    let mut socket = ctx.socket(zmq::REQ).unwrap();
    socket.connect("tcp://127.0.0.1:4243").unwrap();

    // read cmd from line
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    println!("value : {}", input);

    socket.send_str(&input, 0).unwrap();



    thread::spawn(move || {
        let ctx = zmq::Context::new();
        let subscriber = ctx.socket(zmq::SUB).unwrap();

        subscriber
            .connect("tcp://localhost:4242")
            .expect("Failed connecting subscriber !");

        subscriber
            .set_subscribe("".as_bytes())
            .expect("Failed to subscribe to channel A");


        loop {
            let topic = subscriber.recv_msg(0).unwrap();
            let data = subscriber.recv_msg(0).unwrap();

            println!("RECIEVED : {}", std::str::from_utf8(&data).unwrap());
        }
    });
}
