extern crate zmq;
extern crate rand;

use std::thread;
use std::io::{self, Write};

fn start_subscriber_thread() {
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
            let _topic = subscriber.recv_msg(0).unwrap();
            let data = subscriber.recv_msg(0).unwrap();
            let str_data = std::str::from_utf8(&data).unwrap();
            // std::process::Command::new("clear").status().unwrap();
            // println!("RECEIVED : {}", str_data);
        }
    });
}

fn get_req_socket() -> zmq::Socket {
    let ctx = zmq::Context::new();
    let socket = ctx.socket(zmq::REQ).unwrap();
    let x:i32 = (rand::random::<u8>() % 99) as i32;
    let identity = format!("#0x{:0>#2}", x);

    socket.set_identity(&identity.as_bytes()).unwrap();
    socket.connect("tcp://127.0.0.1:4243").unwrap();

    socket
}

fn send_command(socket:zmq::Socket, command:String, args:String) -> Option<String> {
    let input = format!("{}|{}", command, args);
    let mut response = zmq::Message::new().unwrap();

    socket.send_str(&input, 0).unwrap();
    socket.recv(&mut response, 0).unwrap();

    Some(String::from(response.as_str().unwrap()))
}

fn main() {
    start_subscriber_thread();
    let socket = get_req_socket();
    let mut input = String::new();

    print!("Enter your name to connect : ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut input).unwrap();
    let response = send_command(socket, String::from("identity"), input);

    println!("response to connection : {}", response.unwrap());

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
}
