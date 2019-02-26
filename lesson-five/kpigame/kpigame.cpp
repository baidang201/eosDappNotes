#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/dispatcher.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract]] kpigame : public contract{
public:
    using contract::contract;
    [[eosio::action]]
    void hi(name user){
        print("game start");
        require_auth(_self);
        auto values=user.value;
        print("hello user value:", values);
        print(",:hello,:", user);

        action(permission_level{_self, name("active")},
        name("eosio.token"), name("transfer"),
        std::make_tuple(_self, user, asset(1, symbol("EOS", 4)),
        std::string("game send eos")) ).send();
    }

    [[eosio::action]]
    void transfer(name from, name to, asset quantity, string memo) {
        //转账并领取任务
        //print("transfer from ", from);
        string::size_type idx;
        idx = memo.find("taskid:" );
        if(idx != string::npos){
            string id = memo.substr(memo.find("taskid:") + 7, memo.length());
            //print("  id: ", id.c_str());
            auto nID = atoi(id.c_str());
            print("  id: ", nID);

            task_index tasks(_self, _self.value);

            auto taskitem = tasks.find(nID);
            if(taskitem != tasks.end()){
                print("task find! ");
                asset pay = taskitem->reward;
                eosio_assert(quantity.amount >= pay.amount, "transfer error not enough!");

                taskuser_index tasku(_self, from.value);
                auto taskUserItem = tasku.find(taskitem->id);
                if(taskUserItem==tasku.end()){
                    print("taskuser item not  find, new one! ");
                    tasku.emplace(_self, [&](auto &t){
                        t.taskid = taskitem->id;
                        t.is_end = 0;
                        t.start_time = current_time();
                        t.reward = quantity;
                    });
                }
            }
        }
    }

    // [[eosio::action]]
    // void kpi(name from, int score){
    //     action(permission_level{_self, name("active")},
    //     name("eosio.token"), name("transfer"),
    //     std::make_tuple(_self, from, asset(score * 10 * 10000, symbol("EOS", 4)),
    //     std::string("game send eos")) ).send();

    //     work_index works(_self, _self.value);
    //     works.emplace(_self, [&](auto& work){
    //         work.id = works.available_primary_key();
    //         work.worker = from;
    //         work.phone = 0;
    //         work.score = score;
    //         work.token = asset(score * 10 * 10000, symbol("EOS", 4));
    //     });        
    // }

    [[eosio::action]]
    void addtask(string content, uint32_t level, uint64_t end, asset token){
        require_auth(_self);
        task_index tasks(_self, _self.value);

        tasks.emplace(_self, [&](auto &t){
            t.id = tasks.available_primary_key();
            t.level = level;
            t.content = content;
            t.end_time = end;
            t.reward = token;
        });

    }
    [[eosio::action]]
    void cleartask()
    {
        require_auth(_self);
        task_index st(_self, _self.value);
        auto itr = st.begin();
        while(itr != st.end()){
            itr = st.erase(itr);
        }
    }

    [[eosio::action]]
    void confirmtask(uint64_t id, name from){
      require_auth(from);

      task_index tasks(_self, _self.value);

      auto taskitem = tasks.find(id);
      if(taskitem != tasks.end()) {
        taskuser_index tasku(_self, from.value);
        auto taskUserItem = tasku.find(taskitem->id);
        if(taskUserItem!=tasku.end()){            

            if(0 == taskUserItem->is_end){
                tasku.modify(taskUserItem, _self, [&](auto &t){
                    t.is_end = 1;
                    t.end_time = current_time();
                });

                if ( taskUserItem->end_time <= taskitem->end_time) {            
                    //奖励
                    action(permission_level{_self, name("active")},
                    name("eosio.token"), name("transfer"),
                    std::make_tuple(_self, from,  taskitem->reward,
                    std::string("reward send eos")) ).send();

                    //押金
                    action(permission_level{_self, name("active")},
                    name("eosio.token"), name("transfer"),
                    std::make_tuple(_self, from,  taskUserItem->reward,
                    std::string(" mortgage send eos")) ).send();
                }
            }
            
        }
      }
    }

    struct [[eosio::table]] work{
        uint64_t id;
        name worker;
        uint64_t phone;
        asset token;
        uint64_t score;
        uint64_t creat_time = current_time();

        uint64_t primary_key() const {return id;}

        //二级索引
        uint64_t get_phone() const{return phone;}

        //序列号数据
        EOSLIB_SERIALIZE(work, (id)(worker)(phone)(token)(score)(creat_time))
    };
    //实例化
    typedef eosio::multi_index<"work"_n, work,
    indexed_by<"phone"_n, const_mem_fun<work, uint64_t, &work::get_phone>>> work_index;
    


    struct [[eosio::table]] task{
        uint64_t id;
        string content;
        uint32_t level;
        uint64_t end_time;
        asset reward = asset(0, symbol("EOS", 4));

        uint64_t primary_key() const {return id;}
        EOSLIB_SERIALIZE(task, (id)(content)(level)(end_time)(reward))
    };
    typedef eosio::multi_index<"task"_n, task> task_index;

    struct [[eosio::table]] taskuser{
        uint64_t taskid;
        uint32_t is_end;//0 not finish   1 finished
        uint64_t start_time;//take task time
        uint64_t end_time; //upload confirmtask time
        asset reward = asset(0, symbol("EOS", 4));

        uint64_t primary_key() const {return taskid;};
        EOSLIB_SERIALIZE(taskuser, (taskid)(is_end)(start_time)(end_time)(reward))
    };
    typedef eosio::multi_index<"taskuser"_n, taskuser> taskuser_index;


};


#define EOSIO_DISPATCH_CUSTOM(TYPE, MEMBERS) \
extern "C" { \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
   auto self = receiver; \
      if(( code == self&&action != name("transfer").value) || code == name("eosio.token").value && action == name("transfer").value) { \
        switch( action ) { \
            EOSIO_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of this contract to run: eosio_exit(0); */ \
      } \
   } \
} \

EOSIO_DISPATCH_CUSTOM(kpigame, (hi)(transfer)(addtask)(cleartask)(confirmtask))