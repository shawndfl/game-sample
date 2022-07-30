const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    mode: "production",
    entry: {
        index: './src/index.ts'
    },
    devtool: 'inline-source-map',

    module: {
        rules: [
            {
                test: /\.tsx?$/,
                use: 'ts-loader',
                exclude: /node_modules/
            },
        ]
    },
    resolve: {
        extensions: ['.tsx', '.ts', '.js']
    },
    plugins: [
        new HtmlWebpackPlugin(
            {title: 'Production'}
        ),
    ],
    output: {
        filename: '[name].bundle.js',
        path: path.resolve(__dirname, 'docs'),
        clean: true
    },
    performance: {
        maxEntrypointSize: 512000,
        maxAssetSize: 512000
    },
    optimization: {
        chunkIds: 'named',
        splitChunks: {
            chunks: 'all'
        }
    }

};
