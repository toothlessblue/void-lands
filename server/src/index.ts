import express from 'express';
import {isMisspelled} from './spellcheck';
import {render} from './PageRenderer';
import Config from './Config';

const app = express();

// ASSETS

app.get('/assets/engine/GameClient.js', async (req, res) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}/GameEngine/build/emscripten/GameClient/GameClient`);
});

app.get('/assets/engine/GameClient.wasm', async (req, res) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}/GameEngine/build/emscripten/GameClient/GameClient.wasm`);
});

app.get('/w/GameClient.data', async (req, res) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}/GameEngine/build/emscripten/GameClient/GameClient.data`);
});

app.get('/robots.txt', async (req, res, next) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}/robots.txt`);
});

app.get('/favicon.ico', async (req, res, next) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}/assets/images/favicon.svg`);
});

// JS files require special pathing so include statements don't need a file extension
app.get('/assets/js/:file', async (req, res, next) => {
    res.header('Cache-Control', 'public');

    if (req.params.file.indexOf('.js') >= 0) {
        res.sendFile(`${Config.fsRoot}/assets/js/${req.params.file}`);
    } else {
        res.sendFile(`${Config.fsRoot}/assets/js/${req.params.file}.js`);
    }
});

// Every other file can be requested as is
app.get('/assets/**', async (req, res, next) => {
    res.header('Cache-Control', 'public');
    res.sendFile(`${Config.fsRoot}${req.path}`);
});

app.get('/', async (req, res) => {
    res.end(await render(req, 'home.twig'));
});

app.get('/w/:dimension', async (req, res) => {
    const words = req.params.dimension.split('-');

    for (const word of words) {
        if (isMisspelled(word) || word.length > 5) {
            res.end(await render(req, 'invalid.twig'));
            return;
        }
    }

    res.end(await render(req, 'dimension.twig'));
});

app.listen(80, '0.0.0.0');