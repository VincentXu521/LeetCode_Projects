var request = require('request');

// 使用 require 方法加载 fs 核心模块
var fs = require('fs')


var a = process.argv.splice(2)[0];
var url = "https://api.github.com/repos/grandyang/leetcode/issues/" + a;
			
var getIssueOptions = {
	url: url,
	method: "GET",
	json:true,
	headers: {
		"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36"
	}
};




function saveIssue() {
	return new Promise(function(resolve,reject){
        			

				var requestC = request.defaults({jar: true});
				

				requestC(getIssueOptions,function(error,response,body){
					if(error){
						console.log("error occurred: " + error);
						reject(error);
					}
					var path = 'leetcode_solutions/' + a + '.md';
					fs.writeFile(path,'Step1: get issue via url: '+url+' \n '+ 'title:' + body.title+' \n ' + 'body: ' + ' \n ' + body.body,function(error){
						console.log(body.title);
					})

				});

			

	});
}


saveIssue();
