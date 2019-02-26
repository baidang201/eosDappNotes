<template lang="html">
  <div class="invite-buy-box">
    <div class="inner-box">
      <div class="dialog-title">购买</div>
      <div class="input-label">交易数量(KPI)</div>
      <input type="number" v-model="buynum" placeholder="0.0000"  />
     <div class="input-label">{{formatnum(buynum)}}</div>
      <div class="buttons">
        <button @click="cancel">取消</button>
        <button @click="confirm">

          确认</button>
      </div>
    </div>
    <loading v-if="showLoading" @cancel="v => showLoading = v" />
  </div>
</template>

<script>
import loading from "./loading.vue";

export default {
  props: {
    share: String,
    required: true,
    showLoading:false
  },
  data() {
    return {
      buynum: ""
    };
  },
  computed: {
    buynum: {
      set: function(value) {
        this.buynum = value;
      },
      get: function() {
        return this.buynum.replace(/[^0-9]+/g, "");
      }
    }
  },
  methods: {
    cancel() {
      this.$emit("cancel", false);
    },
    confirm() {

      if (this.buynum == "") {
        alert("请输入购买量");
        return;
      }


    },

    formatnum(num) {
      return parseFloat(num * 10).toFixed(4);
    }
  }
  ,
  components: {
    loading
  }
};
</script>

<style lang="scss">
.invite-buy-box {
  position: fixed;
  display: flex;
  align-items: center;
  justify-content: center;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: 1;
  background-color: rgba(35, 50, 67, 0.7);
  .inner-box {
    display: flex;
    flex-direction: column;
    align-items: center;
    width: 650px;
    height: 575px;
    background-color: #ffffff;
    box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
    border-radius: 10px;

    .dialog-title {
      padding-top: 60px;
      font-size: 42px;
      color: #233243;
    }
    .input-label {
      width: 550px;
      margin-top: 40px;
      font-size: 32px;
      color: #233243;
    }
    input {
      display: block;
      font-size: 32px;
      width: 550px;
      line-height: 1;
      padding: 20px 30px;
      margin-top: 6px;
      background-color: #f2f3f6;
      border-radius: 10px;
      outline: none;
      border: none;
    }
    ::-webkit-input-placeholder {
      color: #8993a4;
      font-size: 32px;
    }

    .buttons {
      display: flex;
      justify-content: space-between;
      margin-top: 60px;
      width: 550px;
      button {
        outline: 0;
        width: 265px;
        height: 60px;
        border-radius: 60px;
        font-size: 32px;
        border: 0;
        &:nth-child(1) {
          background-color: #fff;
          color: #2a84f8;
          border: 2px solid #2a84f8;
        }

        &:nth-child(2) {
          background-color: #2a84f8;
          color: #fff;
        }

        &:active {
          opacity: 0.8;
        }
      }
    }
  }
}
</style>
