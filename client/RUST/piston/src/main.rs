extern crate zmq;
extern crate rand;
extern crate piston_window;

use std::thread;
use std::io::{self};
use piston_window::*;


/// Stores application state of inner event loop.
pub struct InnerApp {
    pub title: &'static str,
    pub exit_button: Button,
}

impl InnerApp {
    pub fn run(&mut self, window: &mut PistonWindow) {
        window.set_title(self.title.into());
        while let Some(e) = window.next() {
            window.draw_2d(&e, |c, g| {
                clear([0.5, 0.5, 1.0, 1.0], g);
                ellipse([1.0, 0.0, 0.0, 1.0], [50.0, 50.0, 100.0, 100.0], c.transform, g);
            });
            if let Some(button) = e.press_args() {
                if button == self.exit_button {
                    break;
                }
            }
        }
    }
}

fn close() {
    panic!("CLOSE");
}

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
            let topic = subscriber.recv_msg(0).unwrap();
            let data = subscriber.recv_msg(0).unwrap();

            println!("RECIEVED : {}", std::str::from_utf8(&data).unwrap());
        }
    });
}

fn connect() -> zmq::Socket {
    let ctx = zmq::Context::new();
    let socket = ctx.socket(zmq::REQ).unwrap();
    let x:i32 = (rand::random::<u8>() % 99) as i32;
    let identity = format!("#0x{:0>#2}", x);
    let mut input = String::new();

    socket.set_identity(&identity.as_bytes()).unwrap();
    socket.connect("tcp://127.0.0.1:4243").unwrap();
    io::stdin().read_line(&mut input).unwrap();
    input = format!("identity|{}", input);

    socket
}

fn main() {
    start_subscriber_thread();
    let socket = connect();
    let title = "Softwar in RUST !!";


    let mut window: PistonWindow = WindowSettings::new(title, [640, 480])
        .exit_on_esc(false)
        .build()
        .unwrap_or_else(|e| { panic!("Failed to build PistonWindow: {}", e) });

    window.set_lazy(true);

    while let Some(e) = window.next() {
        window.draw_2d(&e, |c, g| {
            clear([0.5, 1.0, 0.5, 1.0], g);
            rectangle([1.0, 0.0, 0.0, 1.0], [50.0, 50.0, 100.0, 100.0], c.transform, g);
        });

        if e.press_args().is_some() {
            window.set_title(title.into());
            match e.press_args().unwrap() {
                Button::Keyboard(Key::Escape) => close(),
                Button::Keyboard(Key::N) => InnerApp {
                    title: "Inner loop (press X to exit inner loop)",
                    exit_button: Button::Keyboard(Key::X),
                }.run(&mut window),
                _ => {}
            }
        }
    }

    let mut input = String::new();
    socket.send_str(&input, 0).unwrap();
    io::stdin().read_line(&mut input).unwrap();

}
