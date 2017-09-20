extern crate zmq;

fn main() {
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
}
