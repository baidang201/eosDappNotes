const path = require("path");
function resolve(dir) {
  return path.join(__dirname, dir);
}

module.exports = {
  // safari bug 刷新后状态回退到最初版本
  chainWebpack: config => {
    if (process.env.NODE_ENV === "development") {
      config.output.filename("[name].[hash].js").end();
    }
    config.resolve.alias.set("@", resolve("src"));
  },

  pluginOptions: {
    // i18n: {
    //   locale: 'en',
    //   fallbackLocale: 'en',
    //   localeDir: 'locales',
    //   enableInSFC: true
    // }
  }
};
