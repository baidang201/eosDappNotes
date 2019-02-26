<template>
  <div class="undecided">
    <theme @click.native="linkDetail" />

    <!-- 底部按钮 -->
    <div class="myTheme">
      <router-link class="button" to="/">
        游戏中心
      </router-link>
      <router-link class="button" to="/">
        我发起的
      </router-link>
    </div>

  </div>
</template>

<script>



export default {
  data() {
    return {
      FLAG_ADD_THEME: false,
      myJoin: 12,
      myCreate: 5
    };
  },
  methods: {
    // 确认
    addThemeConfirm(obj) {
      // const {title,answer1,answer2} = obj
    },
    // 跳转
    linkDetail(){
      this.$router.push("/themeDetail/01")
    }
  },
  components: {
  }
};
</script>

<style lang="scss">
@import "./style.scss";
</style>
