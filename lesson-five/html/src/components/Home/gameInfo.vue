<template lang="html">
  <div class="game-info-box">
    <div class="inner-box">
      <div class="eto-title">任务内容</div>
      <div class="eto-content">
        <p style="font-size:20px">{{content}}</p>
        <p style="font-size:16px;color:#2a84f8">
          任务奖励：{{reward}}
            </p>
      </div>
      <button @click="cancel">领取</button>
      <button @click="confirm">提交任务</button>

    </div>
  </div>
</template>

<script>
import Scatterutil from "../../utils/scatterutil";

export default {
  props: {
    id:String,
    content:String,
    reward:String,
    required: true
  },
  data() {
    return {
      // id: "",
      // contenct: "",
      // reward:""
    };
  },
  mounted() {
    this.init();
  },
  methods: {
    init() {
    },
    //领取任务调用方法
    async cancel() {
      
      //转账方法
      await Scatterutil.transfer("1","taskid:"+this.id).then(result=>{
        if(result=="true"){
          alert("领取任务成功！")
        }
      });
      this.$emit('close')
    },
    async confirm() {
      await Scatterutil.confirm(""+this.id).then(result=>{
        if(result=="true"){
          alert("提交任务成功！")
        }
      });
      this.$emit('close')
    }
  }
};
</script>

<style lang="scss">
.game-info-box{
  position: fixed;
  display: flex;
  align-items: center;
  justify-content: center;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: 1;
  background-color: rgba(35,50,67,0.7);
  .inner-box{
      width: 650px;
	  height: 550px;
	  background-color: #ffffff;
	  box-shadow: 0px 4px 14px 0px rgba(0, 0, 0, 0.05);
	  border-radius: 10px;

    .eto-title{
      padding-top: 60px;
      font-size: 42px;
      color: #233243;
      text-align: center;
    }

    .eto-content{
      width: 550px;
      margin: 14px auto 0;
      padding: 30px 0;
      h2{
        font-size: 26px;
        color: #233243;
        font-weight: normal;
      }
      p{
        margin-top: 10px;
        font-size: 20px;
        color: #8993a4;
      }
      &:nth-child(2){
        border-bottom: 1px solid  #ebebeb;
      }
    }

    button{
      display: block;
      width: 265px;
      height: 60px;
      margin: 30px auto 0;
      outline: none;
      border-radius: 60px;
      border: 2px solid #2a84f8;
      background-color: #fff;
      font-size: 32px;
      color: #2a84f8;
      &:active{
        background-color: #2a84f8;
        color: #fff;
      }
    }
  }
}
</style>
