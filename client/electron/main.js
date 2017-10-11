const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const path = require('path');
const url = require('url');

let mainWindow;


const createWindow = () => {
    mainWindow = new BrowserWindow({width: 800, height: 600});
    mainWindow.loadURL(url.format({
	pathname: path.join(__dirname, 'index.html'),
	protocol: 'file:',
	slashes: true
    }));
    mainWindow.on('closed', () => mainWindow = null);
};

app.on('ready', createWindow);
app.on('window-all-closed', () =>  'darwin' !== process.platform ? app.quit() : null);
app.on('activate', () => null === mainWindow ? createWindow() : null);
