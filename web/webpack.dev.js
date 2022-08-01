const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');

module.exports = {
    mode: "development",
    entry: './src/index.ts',
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
                use: ['html-loader']
            },
            {
                test: /\.(css|scss)$/,
                use: ["style-loader", "css-loader", "sass-loader"]
            },
            {
                test: /\.svg$/,
                use: ["svg-url-loader"]
            },
            {
                test: /\.png$/,
                use: ["url-loader"]
            },
            {
                test: /\.mp3$/,
                use: ["url-loader"]
            }
        ]
    },
    resolve: {
        extensions: ['.tsx', '.ts', '.js', 'png', 'scss', 'json'],        
        mainFiles: [path.resolve(__dirname, './')],        
    },    
    output: {
        filename: '[name].bundle.js',
        path: path.resolve(__dirname, 'dist'),
        clean: true
    },
    plugins: [
        new HtmlWebpackPlugin(
            {
                template: path.join(__dirname, 'public/index.html'),
                inject: true,
                filename: 'index.html'
            }
        ),
        new MiniCssExtractPlugin(),
    ],

    devServer: {
        watchFiles: [
            'src/**/*.ts', 'public/**/*'
        ],
        static: {
            publicPath: './',
            directory: path.join(__dirname, 'public')
        },
        compress: true,
        client: {
            overlay: true,
            progress: true,
            reconnect: true,
            webSocketTransport: 'ws'
        }
    },

    optimization: {
        chunkIds: 'named'
    }

};
