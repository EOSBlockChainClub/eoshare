const path = require("path");
const webpack = require("webpack");

exports.onCreateWebpackConfig = ({ stage, page, actions }) => {
  actions.setWebpackConfig({
    resolve: {
      modules: [path.resolve(__dirname, "src"), "node_modules"]
    }
  });
};
