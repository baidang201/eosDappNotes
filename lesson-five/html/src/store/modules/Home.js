const Module = {
  state: {
    activeNav: 1 // 激活的底部nav
  },
  mutations: {
    // 修改激活的底部nav
    updateActiveNav(state, payload) {
      state.activeNav = payload;
    }
  }
};

export default Module;
