extern crate zmq;
extern crate rand;

use std::thread;
use std::io::{self, BufRead};

fn main() {
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

    let ctx = zmq::Context::new();
    let mut socket = ctx.socket(zmq::REQ).unwrap();
    let x:i32 = (rand::random::<u8>() % 99) as i32;
    let identity = format!("#0x{:0>#2}", x);
    socket.set_identity(&identity.as_bytes()).unwrap();
    socket.connect("tcp://127.0.0.1:4243").unwrap();

    // read cmd from line
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input = format!("identity|{}", input);
    println!("value : {}", input);

    socket.send_str(&input, 0).unwrap();
    io::stdin().read_line(&mut input).unwrap();

}
