<template lang="html">
  <div class="invite-loading-box">
    <div class="inner-box">
            <ball-scale-ripple-multiple-loader color="#4a87fb " class="loading" size="50px" >
            </ball-scale-ripple-multiple-loader>
    </div>
  </div>
</template>

<script>

import Vue from 'vue';
import 'vue-loaders/dist/vue-loaders.css';
import { BallScaleRippleMultipleLoader, install } from 'vue-loaders';
const VueLoaders = { BallScaleRippleMultipleLoader, install };
Vue.use(VueLoaders);

export default {
};
</script>

<style lang="scss">
.invite-loading-box {
  position: fixed;
  display: flex;
  align-items: center;
  justify-content: center;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: 9999;
  background-color: rgba(35, 50, 67, 0.7); 
  .inner-box {
    .loading{
         margin-top: 10px;
        color: #4a86fb;
     }
  

  }
}
</style>
