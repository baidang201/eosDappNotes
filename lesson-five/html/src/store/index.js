import Vue from "vue";
import Vuex from "vuex";

import Home from "@/store/modules/Home"; // home

Vue.use(Vuex);

export default new Vuex.Store({
  state: {},
  modules: {
    Home
  }
});
