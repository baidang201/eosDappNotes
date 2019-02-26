import Vue from "vue";
import App from "./App.vue";
import router from "./router/index";
import store from "./store/index";
import Axios from "./utils/axios";
import Scatterutil from "./utils/scatterutil";
// var tp = require('./utils/tp')
import "@/assets/flexble";
// 引入iconfont文件
import "@/assets/font/iconfont.css";
import "@/assets/font/iconfont.js"
// import i18n from './i18n'
import eosutil from "./utils/eosutil";

Vue.config.productionTip = false;
Vue.prototype.$http = Axios

Scatterutil.init()
Vue.prototype.$statterUtil = Scatterutil;
Vue.prototype.$eosutil = eosutil;


new Vue({
  router,
  store,
  // i18n,
  render: h => h(App)
}).$mount("#app");
