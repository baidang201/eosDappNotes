<template>
  <div class="home">
    <!-- debug -->
    <game-center v-show="activeNav===1" />
    <!-- 个人中心 -->
    <personal v-show="activeNav===2" />
    <!-- 底部导航栏 -->
    <bottom-nav />
  </div>
</template>

<script>
import gameCenter from "@/components/Home/debug";
import bottomNav from "@/components/Home/bottomNav";
import { mapState } from "vuex";

export default {
  name: "home",
  data() {
    return {
          datas:"",
    };
  },
  computed: {
    ...mapState({
      activeNav: ({ Home }) => Home.activeNav
    })
  },
  components: {
    gameCenter,
    personal: () => import("@/components/Home/personal"),
    bottomNav
  }
};
</script>

