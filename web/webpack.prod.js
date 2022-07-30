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
            {
                test: /\.html$/,
                use: {
                    loader: 'html-loader'
                }
            },
            {
                test: /\.(css|scss)$/,
                use: ["style-loader", "css-loader", "sass-loader"]
            },
            {
                test: /\.svg$/,
                use: {
                    loader: "svg-url-loader"
                }
            },
            {
                test: /\.png$/,
                use: ["file-loader"]
            }
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
        path: path.resolve(__dirname, '../docs'),
        clean: true
    },
    performance: {
        hints: false,
        maxEntrypointSize: 3512000,
        maxAssetSize: 3512000            
    },
    optimization: {
        chunkIds: 'named',
        splitChunks: {
            chunks: 'all'
        }
    }

};
