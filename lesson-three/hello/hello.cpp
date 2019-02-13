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

class [[eosio::contract]] hello : public contract{
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
    void delay(string memeo){
        eosio::transaction t{};
        t.actions.emplace_back(eosio::permission_level(_self, name("active")),
            name("test1"), name("hi"),
            std::make_tuple(name("test2"))
        );
        t.delay_sec = 1;
        t.send(1, _self, false);
        print("delay end!");
    }


    [[eosio::action]]
    void add(name from, uint64_t phone){
        work_index works(_self, _self.value);

        works.emplace(_self, [&](auto& work){
            work.id = works.available_primary_key();
            work.worker = from;
            work.phone = phone;
            work.token = asset(0, symbol("EOS", 4));
        });
    }

    [[eosio::action]]
    void update(uint64_t id, uint64_t phone){
        work_index works(_self, _self.value);

        auto item = works.find(id);
        works.modify(item, _self, [&](auto & work){
            work.phone = phone;
        });
    }

    [[eosio::action]]
    void del(uint64_t id){
        work_index works(_self, _self.value);

        auto item = works.find(id);
        works.erase(item);
    }

    [[eosio::action]]
    void query(uint64_t phone){
        work_index works(_self, _self.value);
        auto workitem = works.get_index<"phone"_n>();
        auto item = workitem.find(phone);
        print("query name is:", item->worker);
    }

    [[eosio::action]]
    void kpi(name from, int score){
        action(permission_level{_self, name("active")},
        name("eosio.token"), name("transfer"),
        std::make_tuple(_self, from, asset(score * 10 * 10000, symbol("EOS", 4)),
        std::string("game send eos")) ).send();

        work_index works(_self, _self.value);
        works.emplace(_self, [&](auto& work){
            work.id = works.available_primary_key();
            work.worker = from;
            work.phone = 0;
            work.score = score;
            work.token = asset(score * 10 * 10000, symbol("EOS", 4));
        });        
    } 

    [[eosio::action]]
    void studentadd(int age){
        student_index students(_self, _self.value);

        students.emplace(_self, [&](auto& stu){
            stu.id = students.available_primary_key();
            stu.age = age;
        });      
    }
    [[eosio::action]]
    void studentdel(int64_t id){
        student_index students(_self, _self.value);

        auto item = students.find(id);
        students.erase(item);
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
    //work_index works(_self, _self.value);

    struct __attribute__((eosio_table)) student{
        uint64_t id;
        int age;

        uint64_t primary_key() const {return id;}
        EOSLIB_SERIALIZE(student, (id)(age));
    };
    typedef eosio::multi_index<"student"_n, student> student_index;
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

EOSIO_DISPATCH_CUSTOM(hello, (hi)(delay)(add)(update)(del)(query)(kpi)(studentadd)(studentdel))