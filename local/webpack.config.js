const path = require('path');

module.exports = {
    mode: 'production',
    entry: {
        main: './src/index.ts',
    },
    output: {
        path: path.resolve(__dirname, '../assets/js'),
        filename: 'app.js' // <--- Will be compiled to this single file
    },
    resolve: {
        extensions: ['.ts', '.tsx', '.js'],
    },
    module: {
        rules: [
            {
                test: /\.tsx?$/,
                loader: 'ts-loader'
            }
        ]
    }
};