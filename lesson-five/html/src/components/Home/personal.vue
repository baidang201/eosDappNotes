<template>
  <div class="personal">
    <div class="user-info">
      <div class="avatar-box">
        <img src="../../assets/images/avatar-girl.jpg" />
      </div>
        <div class="user-name">{{username}}</div>
        <!-- <pacman-loader color="red" size="20px"></pacman-loader> -->
      </div>
      
      <!-- KPI-->
      <div class="eto-info">
        <div class="balance-title">余额(EOS)</div>
        <div class="balance-value">{{usereos}}</div>
        <div class="match-box">
          <div class="box-item">
            <div class="balance-title">KPI数量</div>
            <div class="item-value">0.0000</div>
          </div>
         
          <div class="box-item">
            <div class="balance-title">回购</div>
            <div class="item-value">{{backeot}}</div>
          </div>
        </div>
      </div>

      <!-- 购买和回购 -->
      <div class="tool-box">
        <button  @click="showBuyEotInfo = true">KPI 交易<i class="iconfont e-Path" /></button>
        <button  @click="showSellEotInfo = true">KPI回购<i class="iconfont e-Shape1" /></button>
      </div>

      <!-- 邀请用户 -->
      <div class="invite-box">
        <div class="dialog-item" @click="showEtoInfo = true">
          <span>介绍</span>
          <i class="iconfont e-arrow" />
        </div>
      
      </div>
      
      <loading v-if="showLoading" @confirm="inviteConfirm" @cancel="v => showLoading = v" />

      <!-- 社区介绍 -->
      <eto-info v-if="showEtoInfo" @close="() => showEtoInfo = false" />
      <!-- 购买 -->
      <buyeot v-bind:share="share" v-if="showBuyEotInfo" @confirm="inviteConfirm" @cancel="v => showBuyEotInfo = v" />
      <!-- 回购 -->
      <seleot v-if="showSellEotInfo" @confirm="inviteConfirm" @cancel="v => showSellEotInfo = v" />

    </div>
</template>

<script>
import loading from "./loading.vue";

import Scatterutil from "../../utils/scatterutil";
import etoInfo from "./EtoInfo.vue";
import buyeot from "./buyeot.vue";
import seleot from "./selleot.vue";

export default {
  data() {
    return {
      username: "",
      usereos: "0.0000",
      share: "",
      showLoading: false,
      backeot: "0.0000",
      showEtoInfo: false, // 
      showBuyEotInfo: false, //是否显示购买窗口
      showSellEotInfo: false, //是否显示购买窗口
      showInvitePerson: false // 
    };
  },
  created() {
    // this.init(this);
  },
  //页面加载完成
  mounted() {
    // this.showLoading = true;
    this.init(this);
  },
  methods: {
    /**
     * 
     * @param  {[String]} id [弹窗内输入框内容]
     */
    inviteConfirm(id, val) {
      if (val == "1") {
        this.showEtoInfo = false;
        this.showBuyEotInfo = false;
        this.showSellEotInfo = false;
      }
      this.init();
      this.userinfo(this);
    },
    inviteShare(share) {
      this.share = share;
      this.showInvitePerson = false;
    },
    init() {
      this.share = this.$route.params.id;
      var obj = this;
      console.log("start");
      this.userinfo(this);
    },
    userinfo(obj) {
      obj.$statterUtil.userinfo().then(function(result) {
        console.log(result)
        obj.usereos = result.eos;
        obj.username = result.name;
        obj.showLoading = false;
      });
    }
  },
  components: {
    etoInfo,
    buyeot,
    seleot,
    loading
  }
};

function buyback(obj) {
 
}

function userinfo(obj) {
 
}
</script>

<style lang="scss">
.personal {
  width: 750px;
  margin: 0 auto;
  padding: 50px 20px 140px;
  /* 用户信息 */
  .user-info {
    display: flex;
    align-items: center;
    .avatar-box {
      display: flex;
      justify-content: center;
      align-items: center;
      width: 80px;
      height: 80px;
      border-radius: 50%;
      border: 2px solid #dfdfdf;
      overflow: hidden;
      img {
        display: block;
        width: 100%;
      }
    }
    .user-name {
      font-size: 32px;
      margin-left: 30px;
      color: #233243;
    }
  }

  /* ETO信息 */
  .eto-info {
    width: 710px;
    height: 380px;
    padding: 40px 50px 0;
    margin-top: 30px;
    background-image: linear-gradient(to right, #4a87fb 0%, #b381fd 100%);
    box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
    border-radius: 10px;

    .balance-title {
      font-size: 26px;
      color: rgba(255, 255, 255, 0.6);
    }
    .balance-value {
      margin-top: 2px;
      color: #fff;
      font-size: 70px;
    }
    .match-box {
      margin-top: 60px;
      display: flex;
      justify-content: space-between;
      .box-item {
        width: 50%;
        display: flex;
        flex-direction: column;
        .item-value {
          margin-top: 10px;
          color: #fff;
          font-size: 36px;
        }
      }
    }
  }

  /* ETO的购买和回购 */
  .tool-box {
    display: flex;
    height: 105px;
    margin-top: 20px;
    background-color: #ffffff;
    box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
    border-radius: 10px;
    button {
      position: relative;
      outline: 0;
      border: 0;
      background-color: #fff;
      width: 50%;
      font-size: 32px;
      color: #233243;
      &:first-child:after {
        position: absolute;
        right: 0;
        top: 23px;
        content: "";
        display: block;
        width: 1px;
        height: 60px;
        background-color: #ebebeb;
      }
      .iconfont {
        font-size: 40px;
        color: #4a86fb;
        margin-left: 10px;
      }
      &:active {
        opacity: 0.8;
      }
    }
  }

  /* 邀请用户 */
  .invite-box {
    padding: 30px 30px 0;
    margin-top: 20px;
    width: 710px;
    height: 297px;
    background-color: #ffffff;
    box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
    border-radius: 10px;
    .invite-user {
      display: flex;
      justify-content: flex-end;
      align-items: center;
      padding: 30px 0;
      height: 130px;
      background: url("../../assets/images/personal-invite.png") no-repeat
        center;
      background-size: 100%;
      box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
      border-radius: 100px;
      span {
        font-size: 26px;
        color: #fff;
        margin-right: 17px;
      }
      button {
        outline: 0;
        border: 0;
        width: 90px;
        height: 90px;
        border-radius: 50%;
        margin-right: 20px;
        background-image: linear-gradient(#ffc85e 0%, #ff9820 100%);
        box-shadow: 0px 0px 4px 4px rgba(17, 20, 75, 0.2);
        font-size: 29px;
        color: #fff;
        font-weight: bold;
        &:active {
          opacity: 0.8;
        }
      }
    }
    .dialog-item {
      margin-top: 30px;
      height: 105px;
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-top: 1px solid #ebebeb;
      font-size: 32px;
      color: #233243;
      .iconfont {
        font-size: 30px;
        color: #8993a4;
      }
      &:active {
        opacity: 0.8;
      }
    }
  }
}
</style>
