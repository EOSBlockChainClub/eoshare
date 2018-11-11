const path = require("path");
const fs = require("fs");
const webpack = require("webpack");
const lessToJs = require("less-vars-to-js");
const themeVariables = lessToJs(
  fs.readFileSync(path.join(__dirname, "./src/less/theme.less"), "utf8")
);

exports.onCreateWebpackConfig = ({ stage, page, actions }) => {
  actions.setWebpackConfig({
    module: {
      rules: [
        {
          test: /\.less$/,
          use: [
            {
              loader: "style-loader",
              options: {
                sourceMap: process.env.NODE_ENV !== "production"
              }
            },
            {
              loader: "css-loader",
              options: {
                importLoaders: 1,
                sourceMap: process.env.NODE_ENV !== "production"
              }
            },
            {
              loader: "less-loader",
              options: {
                modifyVars: themeVariables,
                javascriptEnabled: true
              }
            }
          ]
        }
      ]
    },
    resolve: {
      modules: [path.resolve(__dirname, "src"), "node_modules"]
    }
  });
};
