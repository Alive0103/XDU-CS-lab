//logs.js
const util = require('../../utils/util.js')

Page({
  data: {
    logs: [],
    activeIndex:0,
    dayList:[],
    list:[],
    sum:[
      {
        title:'今日专注次数',
        val:'0'
      },
      {
        title: '累计专注次数',
        val: '0'
      },
      {
        title: '今日专注时长',
        val: '0分钟'
      },
      {
        title: '累计专注时长',
        val: '0分钟'
      }
    ],
    cateArr: [
      {
        icon: 'work',
        text: '工作'
      },
      {
        icon: 'study',
        text: "学习",
      },
      {
        icon: 'think',
        text: '思考'
      },
      {
        icon: 'write',
        text: '写作'
      },
      {
        icon: 'sport',
        text: '运动'
      },
      {
        icon: 'read',
        text: "阅读"
      }
    ]
  },
  onShow: function () {
    // this.setData({
    //   logs: (wx.getStorageSync('logs') || []).map(log => {
    //     return util.formatTime(new Date(log))
    //   })
    // })
    var logs = wx.getStorageSync('logs') || [];
    // console.log(logs)//;
    var day = 0;
    var total = logs.length;
    var dayTime = 0;
    var totalTime = 0;
    var dayList = [];
    var List = [];
    if(logs.length > 0) {
      for(var i=0;i<logs.length;i++) {
        if(logs[i].date.substr(0,10) == util.formatTime(new Date).substr(0,10)) {
          day = day + 1;
          dayTime = dayTime + parseInt(logs[i].time);
          dayList.push(logs[i]);
        }
        totalTime = totalTime + parseInt(logs[i].time);
      }
      this.setData({
        dayList:dayList,
        list:dayList,
        'sum[0].val':day,
        'sum[1].val':total,
        'sum[2].val':dayTime+'分钟',
        'sum[3].val':totalTime+'分钟'
      })
    }

  },
  changeType: function (e) {
    var index = e.currentTarget.dataset.index;
    if(index == 0) {
      this.setData({
        list:this.data.dayList
      })
    } else if(index == 1) {
      var logs = wx.getStorageSync('logs') || [];
      this.setData({
        list:logs
      })
    }
    this.setData({
      activeIndex: index
    })
  },

  clearData:function(){
    var _this = this;
    wx.showModal({
      title: 'Warning!',
      content: '这将会删除您所有记录',
      success: function (res) {
        if (res.confirm) {  
          wx.clearStorage();
          wx.showToast({
            title: '已删除所有记录',
            duration: 2000     
          })
        } 
      }
    })
  }
})
