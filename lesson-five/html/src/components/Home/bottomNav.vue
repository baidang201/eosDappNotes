<template>
  <div class="bottom-nav">
    <label class="nav-item">
      <input type="radio" :value="1" v-model="activeNav" />
      <div class="content">
        <svg class="icon" aria-hidden="true" v-show="activeNav===2">
          <use xlink:href="#e-shejiao"></use>
        </svg>
        <svg class="icon" aria-hidden="true" v-show="activeNav===1">
          <use xlink:href="#e-Group"></use>
       </svg>
        <span>任务中心</span>
      </div>
    </label>
    <label class="nav-item">
      <input type="radio" :value="2" v-model="activeNav" />
      <div class="content">
        <svg class="icon" aria-hidden="true" v-show="activeNav===1">
          <use xlink:href="#e-Group1"></use>
        </svg>
        <svg class="icon" aria-hidden="true" v-show="activeNav===2">
          <use xlink:href="#e-geren"></use>
        </svg>
        <span>个人中心</span>
      </div>
    </label>
  </div>
</template>

<script>
export default {
  computed: {
    activeNav: {
      get() {
        return this.$store.state.Home.activeNav;
      },
      set(value) {
        this.$store.commit("updateActiveNav", value);
      }
    }
  }
};
</script>

<style lang="scss">
// 底部导航栏
.bottom-nav {
  position: fixed;
  left: 50%;
  bottom: 0;
  transform: translateX(-50%);
  display: flex;
  width: 750px;
  height: 100px;
  background-color: #fff;
  border-top: 1px solid #ebebeb;
  .nav-item {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 50%;
    font-size: 32px;
    color: #999;
    input[type="radio"] {
      display: none;
    }
    input[type="radio"]:checked + .content {
      color: #4a86fb;
      font-weight: bold;
    }
    .icon {
      font-size: 44px;
      margin-right: 6px;
    }
  }
}
</style>
