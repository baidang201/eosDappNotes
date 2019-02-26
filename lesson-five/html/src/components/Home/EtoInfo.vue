<template lang="html">
  <div class="eto-info-box">
    <div class="inner-box">
      <div class="eto-title">KPI</div>
      <div class="eto-content">
        <h2>介绍</h2>
        <p >完成相应的任务经过系统评判后既会获得相应代币奖励</p>
      </div>
      <button @click="$emit('close')">确定</button>
    </div>
  </div>
</template>

<script>

export default {
};
</script>

<style lang="scss">
.eto-info-box{
  position: fixed;
  display: flex;
  align-items: center;
  justify-content: center;
  top: 150px;
  left: 0;
  width: 100%;
  height: 50%;
  z-index: 1;
    background: rgba(35,50,67,0.7);

  background-color: rgba(35,50,67,0.7);
  .inner-box{
    width: 850px;
	  height: 100%;
	  background-color: #ffffff;
	  box-shadow: 0px 4px 10px 0px rgba(0, 0, 0, 0.05);
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
      padding: 20px 0;
      h2{
        font-size: 22px;
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
