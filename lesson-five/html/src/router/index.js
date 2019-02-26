import Vue from "vue";
import Router from "vue-router";

Vue.use(Router);

const router = new Router({
  mode: "history",
  base: process.env.BASE_URL,
  routes: [
    {
      path: "/",
      name: "home",
      component: () => import("@/views/Home"),
      meta: {
        title: " GAME Center"
      }
    },
    {
      path: "/share/:id",
      name: "home",
      component: () => import("@/views/Home"),
      meta: {
        title: "游戏中心"
      }
    }

  ]
});

router.beforeEach((to, from, next) => {
  to.meta.title ? (document.title = to.meta.title) : null;
  next();
});

export default router;
