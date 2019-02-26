import Vue from 'vue'
//加载scatter
import ScatterJS from 'scatterjs-core';
import ScatterEOS from 'scatterjs-plugin-eosjs2';

import { Api, JsonRpc, RpcError } from 'eosjs';

//初始化对象（使用eosj 或者scattereth，或者scattertron）
ScatterJS.plugins(new ScatterEOS());

let scatter = null;
let eosapi;

const network = {
    blockchain:'eos',
    host:'139.199.183.236',
    port:8888,
    protocol:'http',
    chainId:'00239dc32b254c94d366a0c4e44efc88589eb307f6e2f77c80cbe926da5b0c12'
};

const rpc = new JsonRpc('http://139.199.183.236:8888');

const requiredFields = { accounts: [network] };

//export命令定义了模块的对外接口
export default class Scatterutil {

    static async init() {
        console.log("Scatterutil init!")
        //ES6 Promise
        return new Promise(async resolve => {
            ScatterJS.scatter.connect("kpigame").then(connected => {
                if (!connected) {
                    resolve("false");
                    return false;
                }
                scatter = ScatterJS.scatter;
                //
                eosapi = scatter.eos(network, Api, { rpc, beta3: true });
                // 必须清空对象防止泄露对象。
                window.scatter = null;
                resolve("true");
            })
        });
    }

    //获取授权用户
    static async userinfo() {

        return new Promise(async resolve => {
            let account = { name: "", eos: 0 };
            scatter.getIdentity(requiredFields).then(() => {
                
                if (scatter != null) {
                    if (scatter.identity != null) {
                        //获取EOS的account
                        const accounts = scatter.identity.accounts.find(x => x.blockchain === 'eos');
                        account.name = accounts.name;
                    }
                }
            }).then(() => {
                rpc.get_currency_balance('eosio.token',  account.name, 'EOS')
                .then((balance) =>{           
                    account.eos = balance[0].split(" ")[0] 
                    resolve(account);
                });
            })
            .catch(error => {
                resolve("");
            console.error(error);
        });
        });
        };

   
    //转账
    static async transfer(num, memo) {
        console.log('in !!transfer')
        console.log(num)
        if (scatter == null) {
            alert("请安装scatter插件！");
        }
        return new Promise(async resolve => {
            //
            scatter.getIdentity(requiredFields).then(() => {
                const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
                const transactionOptions = { authorization: [`${account.name}@${account.authority}`] };

                console.log('before !!transact')
    eosapi.transact({
        actions: [{
            account: 'eosio.token',
            name: 'transfer',
            authorization: [{
                actor: account.name,
                permission: account.authority ,
            }],
            data: {
                from: account.name,
                to: 'test1',
                quantity: '1.0000 EOS',
                memo: memo
            },
        }]
    }, {
        blocksBehind: 3,
        expireSeconds: 300,
    }).then(result => {
        console.log(`transfer Transaction ID: ${result.transaction_id}`);
        resolve("true");
    }).catch(error => {
        console.log(error);
    });

            }).catch(error => {
                console.error(error);
                resolve("false");
            });
        });
    };


    //提交任务
    static async confirm(num) {
        console.log("confirm", num)
        if (scatter == null) {
            alert("请安装scatter插件！");
        }

        return new Promise(async resolve =>{
            scatter.getIdentity(requiredFields).then(() => {
                const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
                const transactionOptions = { authorization: [`${account.name}@${account.authority}`] };
            
                eosapi.transact({
                    actions:[{
                        account: 'test1',     //contract name
                        name: 'confirmtask',  //action
                        authorization:[{
                            actor: account.name,
                            permission: account.authority,
                        }],
                        data:{
                            id: num,
                            from: account.name
                        }
                    }]
                }, {
                    blocksBehind:3,
                    expireSeconds: 300,
                }).then(result =>{
                    console.log(`confirm Transaction ID: ${result.transaction_id}`);
                    resolve("true");
                }).catch(error =>{
                    console.log(error)
                })

            }).catch(error => {
                console.error(error);
                resolve("false");
            }); 
        })
    }

}
