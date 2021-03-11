function hasParent(node, parent) {
    while (node) {
        if (node === parent) {
        return true;
        }
        node = node.parentNode;
    }
    return false;
}

var bluebox = {
    props:{
        msg:String
    },
    template:`<div   class="button" style="display:inline-block;background-color:#2C72DE;border-radius:15px;color:white;padding:5px 10px;margin-right:5px;">{{msg}}  <i class="fas fa-times" @click="$emit('delete',$event)" ></i></div>`
};


var divinput = {
    props:{
        options:Array,
    },
    components:{
        'bluebox':bluebox
    },
    template:`
        <div style="height:37px;border:1px solid #DBDBDB;padding:5px;border-radius:5px;width:350px;overflow:hidden;position:relative;">
            <div style="white-space:nowrap;text-align:left;">
                <bluebox v-for="option in options" :msg="option" @delete="$emit('delete',$event)"></bluebox>
            <div>
            <i class="fas fa-plus" style="width:20px;position:absolute;right:10px;top:8px;color:#C1C1C1;padding:3px 2px 3px 4px;border:1px solid #DFDFDF;border-radius:50%;"></i>
        </div>`
};

var checkbox = {
    props:{
        options:Array
    },
    data:function(){
        return {
            text:"",
            options_:this.options.map(x=>({'chinese':x.chinese,'english':x.english,'show':true}))
        }
    },
    methods:{
        type:function(event){
            var search = event.target.nextElementSibling;
            search.style.display='none';
        },
        leave:function(event){
            var target = event.target;
            var search = event.target.nextElementSibling;
            if(target.value=="")search.style.display='block';
        },
        oninput:function(event){
            var reg = new RegExp(this.text);
            for(let option of this.options_){
                if ((this.text=='') || reg.test(option.chinese))
                    option.show=true;
                else
                    option.show=false;
            }
        }
    },
    template:`
    <div style="width:350px;box-shadow:0 5px 5px 2px #CBCBCB;" >
        <div style="height:40px;background-color:#F5F5F5;overflow:hidden;">
            <div style="background-color:white;height:30px;width:80%;margin:5px auto;position:relative;border:1px solid #D5D5D5;border-radius:50px;display:flex;align-items:center;">
                <i class="fas fa-search" style="margin:auto 10px;color:#DBDBDB;"></i>
                <input style="border:none;outline:none;z-index:1;background-color:transparent;" @focus="type($event)" @blur="leave($event)" v-model="text" @input="oninput($event)">
                <div style="color:#9E9E9E;position:absolute;left:35px;z-index:0;">搜索</div>
            </div>
        </div>
        <form style="height:170px;">
            <div v-for="option in options_" style="display:flex;align-items:center;margin-top:20px;" v-show="option.show" >
                <input type="checkbox" :name="option.english" style="width:15px;height:15px;margin-left:45px;border:1px solid #DBDBDB;border-radius:3px;" @click="$emit('check',$event)"><span style="margin-left:20px;font-weight:500;">{{option.chinese}}</span>
            </div>
        </form>
    <div>`
};
var dropdown = {
    props:{
        options:Array
    },
    mounted:function(){
        
    },
    data:function(){
        return {
            optionChinese:[],
            show_drop:false,
            unadd:true,
            s:new Set()
        }
    },
    components:{
        'divinput':divinput,
        'checkbox':checkbox,
    },
    methods:{
        onclick:function(event){
            this.show_drop = true;
            if(this.unadd){
                document.addEventListener('click',event_=>{
                    if(!hasParent(event_.target,event.currentTarget))
                        this.show_drop = false;
                });
                this.unadd = false;
            };
        },
        oncheck:function(event){
            var target = event.target;
            if(!this.s.has(target)){
                this.s.add(target);
            }else{
                this.s.delete(target);
            }
            this.optionChinese = Array.from(this.s).map(x=>x.nextElementSibling.innerText);
        },
        ondelete:function(event){
            var str = event.target.parentElement.innerText.trim();
            for(let x of this.s){
                if(x.nextElementSibling.innerText == str){ 
                    x.click();
                    return;
                }
            }
        }
    },
    template:`
        <div style="display:inline-flex;flex-direction:column;justify-content:center;align-items:center;" @click.stop="onclick($event)">
            <divinput :options="optionChinese" @delete="ondelete($event)"></divinput>
            <checkbox :options=options v-show="show_drop" @check="oncheck($event)"></checkbox>
        </div>
    `
}
const items = [{'chinese':'变更中','english':'changing'},
{'chinese':'未生效','english':'unactive'},
{'chinese':'作废','english':'depracated'},
{'chinese':'正常','english':'normal'},
{'chinese':'审核','english':'censoring'}];
export {dropdown,items}