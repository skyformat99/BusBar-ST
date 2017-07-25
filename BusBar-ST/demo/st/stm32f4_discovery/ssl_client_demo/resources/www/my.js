function createXmlRequest() 
{ 
   if(window.ActiveXObject) { 
      var xmlHttps=["Microsoft.XMLHTTP","MSXML2.XMLHttp.5.0","MSXML2.XMLHttp4.0", "MSXML2.XMLHttp3.0","MSXML2.XMLHttp"];           
       try  { 
         for(var i=0;i<xmlHttps.length;i++) { 
           var xmlHttp=new ActiveXObject(xmlHttps[i]); 
           return xmlHttp; 
         } 
      } catch (error) { } 
    } else  { 
       var xmlHttp=new XMLHttpRequest(); 
       return xmlHttp;
   }
}
function ajaxget(xmlHttp, url) {
    xmlHttp.open("GET", url, true);
    xmlHttp.setRequestHeader("If-Modified-Since", "0");
    xmlHttp.send("");
}


 
