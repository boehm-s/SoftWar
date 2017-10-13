// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

const zmq = require('zeromq');
const req_socket = zmq.socket('req');
const sub_socket = zmq.socket('sub');

const genID = () => {
    const n = Math.floor(Math.random() * (99 - 0));
    const str = n.toString();
    return (2 !== str.length)
	? '#0x0' + str
	: '#0x' + str;
};

req_socket.identity = genID();
req_socket.connect('tcp://127.0.0.1:4243');
sub_socket.connect('tcp://127.0.0.1:4242');
sub_socket.subscribe('');

module.exports = {req_socket, sub_socket};
