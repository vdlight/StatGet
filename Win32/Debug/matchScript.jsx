#target photoshop

var headline = "Omgång omg. Nr";
var matchDate = "2015-02-11";
var result = "3-0";
var awayTeamShort = "PAN";
var awayTeamName = "IK Pantern";
var homeTeamShort = "TRA";
var homeTeamName = "Tranås AIF IF";
var periods = "3";
var homeShots = new Array("10", "9", "8");
var awayShots = new Array("8", "11", "7");

var period1_goal_time = new Array("15:54");
var period1_goal_teamStat = new Array("PP1");
var period1_goal= new Array("1-0");
var period1_goal_team = new Array("h");
var period1_scorer = new Array("22. Eriksson, Johan");
var period1_ass1 = new Array("7. Johansson, Adam");
var period1_ass2 = new Array("18. Josefsson, Thobias");

var period2_goal_time = new Array("37:35", "38:39");
var period2_goal_teamStat = new Array("EQ", "PS");
var period2_goal= new Array("2-0", "3-0");
var period2_goal_team = new Array("h", "h");
var period2_scorer = new Array("11. Gustafsson, Eric", "9. Erdugan, Joakim");
var period2_ass1 = new Array("10. Skoog, Anders", "N/A");
var period2_ass2 = new Array("N/A", "N/A");

var period3_goal_time = new Array();
var period3_goal_teamStat = new Array();
var period3_goal= new Array();
var period3_goal_team = new Array();
var period3_scorer = new Array();
var period3_ass1 = new Array();
var period3_ass2 = new Array();

var period4_goal_time = new Array();
var period4_goal_teamStat = new Array();
var period4_goal= new Array();
var period4_goal_team = new Array();
var period4_scorer = new Array();
var period4_ass1 = new Array();
var period4_ass2 = new Array();

var penalties_stat = new Array();
var penalties_res = new Array();
var penalties_team = new Array();
var penalties_scorer = new Array();


    // Consts  
    var scriptPath = "F:/TAIF/Scripttest/New Folder/";
    var matchInfo= "highlights_matchinfo_template_v2.psd";
    var goal = "highlights_goal_template_v2.psd";
    var goalSummary = "highlights_summary_template_v2.psd";
    
    
    var result = "1-2" ; // TODO!!!
    
    var ColorYellow_Red = 245.0;
    var ColorYellow_Green = 197.0;
    var ColorYellow_Blue = 3.0;

    //var doc = app.activeDocument;
    //var layer = doc.activeLayer;
    //var group = layer.parent.layers;
  
  
    // --------- functions -------------
    function openPSD(filePath) {
            var fileRef = File( scriptPath+ filePath);
            var docRef = app.open(fileRef);
    }
//------------------------
   
    function savePNG(saveFile) {
        var file = File(scriptPath + saveFile);  
        var pngSaveOptions = new PNGSaveOptions();
 
        activeDocument.saveAs(file, pngSaveOptions, true, Extension.LOWERCASE); 
    }
//------------------------

    function closePSD() {
        activeDocument.close(SaveOptions.DONOTSAVECHANGES);
        
    }

function writePlayer(playerName, numberCnt, leftAlign) {
  var maxString  = 70;
  var textAlign;
  
    if (leftAlign) {
        textAlign = "dirLeftToRight"; 
    }
    else {
        textAlign = "dirRightToLeft";
    }
  var doc = app.activeDocument;
   var layer = doc.activeLayer;
   var size = layer.textItem.size;    
    
    var idsetd = charIDToTypeID( "setd" );
    var desc3 = new ActionDescriptor();
    var idnull = charIDToTypeID( "null" );
        var ref2 = new ActionReference();
        var idTxLr = charIDToTypeID( "TxLr" );
        var idOrdn = charIDToTypeID( "Ordn" );
        var idTrgt = charIDToTypeID( "Trgt" );
        ref2.putEnumerated( idTxLr, idOrdn, idTrgt );
    desc3.putReference( idnull, ref2 );
    var idT = charIDToTypeID( "T   " );
        var desc4 = new ActionDescriptor();
        var idTxt = charIDToTypeID( "Txt " );
        desc4.putString( idTxt, playerName);
        var idwarp = stringIDToTypeID( "warp" );
            var desc5 = new ActionDescriptor();
            var idwarpStyle = stringIDToTypeID( "warpStyle" );
            var idwarpStyle = stringIDToTypeID( "warpStyle" );
            var idwarpNone = stringIDToTypeID( "warpNone" );
            desc5.putEnumerated( idwarpStyle, idwarpStyle, idwarpNone );
            var idwarpValue = stringIDToTypeID( "warpValue" );
            desc5.putDouble( idwarpValue, 0.000000 );
            var idwarpPerspective = stringIDToTypeID( "warpPerspective" );
            desc5.putDouble( idwarpPerspective, 0.000000 );
            var idwarpPerspectiveOther = stringIDToTypeID( "warpPerspectiveOther" );
            desc5.putDouble( idwarpPerspectiveOther, 0.000000 );
            var idwarpRotate = stringIDToTypeID( "warpRotate" );
            var idOrnt = charIDToTypeID( "Ornt" );
            var idHrzn = charIDToTypeID( "Hrzn" );
            desc5.putEnumerated( idwarpRotate, idOrnt, idHrzn );
        var idwarp = stringIDToTypeID( "warp" );
        desc4.putObject( idwarp, idwarp, desc5 );
        var idtextGridding = stringIDToTypeID( "textGridding" );
        var idtextGridding = stringIDToTypeID( "textGridding" );
        var idNone = charIDToTypeID( "None" );
        desc4.putEnumerated( idtextGridding, idtextGridding, idNone );
        var idOrnt = charIDToTypeID( "Ornt" );
        var idOrnt = charIDToTypeID( "Ornt" );
        var idHrzn = charIDToTypeID( "Hrzn" );
        desc4.putEnumerated( idOrnt, idOrnt, idHrzn );
        var idAntA = charIDToTypeID( "AntA" );
        var idAnnt = charIDToTypeID( "Annt" );
        var idAnSm = charIDToTypeID( "AnSm" );
        desc4.putEnumerated( idAntA, idAnnt, idAnSm );
        var idtextShape = stringIDToTypeID( "textShape" );
            var list1 = new ActionList();
                var desc6 = new ActionDescriptor();
                var idTEXT = charIDToTypeID( "TEXT" );
                var idTEXT = charIDToTypeID( "TEXT" );
                var idPnt = charIDToTypeID( "Pnt " );
                desc6.putEnumerated( idTEXT, idTEXT, idPnt );
                var idOrnt = charIDToTypeID( "Ornt" );
                var idOrnt = charIDToTypeID( "Ornt" );
                var idHrzn = charIDToTypeID( "Hrzn" );
                desc6.putEnumerated( idOrnt, idOrnt, idHrzn );
                var idTrnf = charIDToTypeID( "Trnf" );
                    var desc7 = new ActionDescriptor();
                    var idxx = stringIDToTypeID( "xx" );
                    desc7.putDouble( idxx, 1.000000 );
                    var idxy = stringIDToTypeID( "xy" );
                    desc7.putDouble( idxy, 0.000000 );
                    var idyx = stringIDToTypeID( "yx" );
                    desc7.putDouble( idyx, 0.000000 );
                    var idyy = stringIDToTypeID( "yy" );
                    desc7.putDouble( idyy, 1.000000 );
                    var idtx = stringIDToTypeID( "tx" );
                    desc7.putDouble( idtx, 0.000000 );
                    var idty = stringIDToTypeID( "ty" );
                    desc7.putDouble( idty, 0.000000 );
                var idTrnf = charIDToTypeID( "Trnf" );
                desc6.putObject( idTrnf, idTrnf, desc7 );
                var idrowCount = stringIDToTypeID( "rowCount" );
                desc6.putInteger( idrowCount, 1 );
                var idcolumnCount = stringIDToTypeID( "columnCount" );
                desc6.putInteger( idcolumnCount, 1 );
                var idrowMajorOrder = stringIDToTypeID( "rowMajorOrder" );
                desc6.putBoolean( idrowMajorOrder, true );
                var idrowGutter = stringIDToTypeID( "rowGutter" );
                var idPnt = charIDToTypeID( "#Pnt" );
                desc6.putUnitDouble( idrowGutter, idPnt, 0.000000 );
                var idcolumnGutter = stringIDToTypeID( "columnGutter" );
                var idPnt = charIDToTypeID( "#Pnt" );
                desc6.putUnitDouble( idcolumnGutter, idPnt, 0.000000 );
                var idSpcn = charIDToTypeID( "Spcn" );
                var idPnt = charIDToTypeID( "#Pnt" );
                desc6.putUnitDouble( idSpcn, idPnt, 0.000000 );
                var idframeBaselineAlignment = stringIDToTypeID( "frameBaselineAlignment" );
                var idframeBaselineAlignment = stringIDToTypeID( "frameBaselineAlignment" );
                var idalignByAscent = stringIDToTypeID( "alignByAscent" );
                desc6.putEnumerated( idframeBaselineAlignment, idframeBaselineAlignment, idalignByAscent );
                var idfirstBaselineMinimum = stringIDToTypeID( "firstBaselineMinimum" );
                var idPnt = charIDToTypeID( "#Pnt" );
                desc6.putUnitDouble( idfirstBaselineMinimum, idPnt, 0.000000 );
                var idbase = stringIDToTypeID( "base" );
                    var desc8 = new ActionDescriptor();
                    var idHrzn = charIDToTypeID( "Hrzn" );
                    desc8.putDouble( idHrzn, 0.000000 );
                    var idVrtc = charIDToTypeID( "Vrtc" );
                    desc8.putDouble( idVrtc, 0.000000 );
                var idPnt = charIDToTypeID( "Pnt " );
                desc6.putObject( idbase, idPnt, desc8 );
            var idtextShape = stringIDToTypeID( "textShape" );
            list1.putObject( idtextShape, desc6 );
        desc4.putList( idtextShape, list1 );
        var idTxtt = charIDToTypeID( "Txtt" );
            var list2 = new ActionList();
                var desc9 = new ActionDescriptor();
                var idFrom = charIDToTypeID( "From" );
                desc9.putInteger( idFrom, 0 );
                var idT = charIDToTypeID( "T   " );
                desc9.putInteger( idT, numberCnt );
                var idTxtS = charIDToTypeID( "TxtS" );
                    var desc10 = new ActionDescriptor();
                    var idstyleSheetHasParent = stringIDToTypeID( "styleSheetHasParent" );
                    desc10.putBoolean( idstyleSheetHasParent, true );
                    var idfontPostScriptName = stringIDToTypeID( "fontPostScriptName" );
                    desc10.putString( idfontPostScriptName, """BebasNeue""" );
                    var idFntN = charIDToTypeID( "FntN" );
                    desc10.putString( idFntN, """Bebas Neue""" );
                    var idFntS = charIDToTypeID( "FntS" );
                    desc10.putString( idFntS, """Regular""" );
                    var idScrp = charIDToTypeID( "Scrp" );
                    desc10.putInteger( idScrp, 0 );
                    var idFntT = charIDToTypeID( "FntT" );
                    desc10.putInteger( idFntT, 0 );
                    var idSz = charIDToTypeID( "Sz  " );
                    var idPnt = charIDToTypeID( "#Pnt" );
                    desc10.putUnitDouble( idSz, idPnt, 124.370232 );
                    var idautoLeading = stringIDToTypeID( "autoLeading" );
                    desc10.putBoolean( idautoLeading, false );
                    var idLdng = charIDToTypeID( "Ldng" );
                    var idPnt = charIDToTypeID( "#Pnt" );
                    desc10.putUnitDouble( idLdng, idPnt, 41.289421 );
                    var idClr = charIDToTypeID( "Clr " );
                        var desc11 = new ActionDescriptor();
                        var idRd = charIDToTypeID( "Rd  " );
                        desc11.putDouble( idRd, ColorYellow_Red );
                        var idGrn = charIDToTypeID( "Grn " );
                        desc11.putDouble( idGrn, ColorYellow_Green );
                        var idBl = charIDToTypeID( "Bl  " );
                        desc11.putDouble( idBl, ColorYellow_Blue );
                    var idRGBC = charIDToTypeID( "RGBC" );
                    desc10.putObject( idClr, idRGBC, desc11 );
                var idTxtS = charIDToTypeID( "TxtS" );
                desc9.putObject( idTxtS, idTxtS, desc10 );
            var idTxtt = charIDToTypeID( "Txtt" );
            list2.putObject( idTxtt, desc9 );
                var desc12 = new ActionDescriptor();
                var idFrom = charIDToTypeID( "From" );
                desc12.putInteger( idFrom,numberCnt );
                var idT = charIDToTypeID( "T   " );
                desc12.putInteger( idT,maxString );
                var idTxtS = charIDToTypeID( "TxtS" );
                    var desc13 = new ActionDescriptor();
                    var idstyleSheetHasParent = stringIDToTypeID( "styleSheetHasParent" );
                    desc13.putBoolean( idstyleSheetHasParent, true );
                    var idfontPostScriptName = stringIDToTypeID( "fontPostScriptName" );
                    desc13.putString( idfontPostScriptName, """BebasNeue""" );
                    var idFntN = charIDToTypeID( "FntN" );
                    desc13.putString( idFntN, """Bebas Neue""" );
                    var idFntS = charIDToTypeID( "FntS" );
                    desc13.putString( idFntS, """Regular""" );
                    var idScrp = charIDToTypeID( "Scrp" );
                    desc13.putInteger( idScrp, 0 );
                    var idFntT = charIDToTypeID( "FntT" );
                    desc13.putInteger( idFntT, 0 );
                    var idSz = charIDToTypeID( "Sz  " );
                    var idPnt = charIDToTypeID( "#Pnt" );
                    desc13.putUnitDouble( idSz, idPnt, 124.370232 );
                    var idautoLeading = stringIDToTypeID( "autoLeading" );
                    desc13.putBoolean( idautoLeading, false );
                    var idLdng = charIDToTypeID( "Ldng" );
                    var idPnt = charIDToTypeID( "#Pnt" );
                    desc13.putUnitDouble( idLdng, idPnt, 41.289421 );
                    var idClr = charIDToTypeID( "Clr " );
                        var desc14 = new ActionDescriptor();
                        var idRd = charIDToTypeID( "Rd  " );
                        desc14.putDouble( idRd, 255.000000 );
                        var idGrn = charIDToTypeID( "Grn " );
                        desc14.putDouble( idGrn, 255.000000 );
                        var idBl = charIDToTypeID( "Bl  " );
                        desc14.putDouble( idBl, 255.000000 );
                    var idRGBC = charIDToTypeID( "RGBC" );
                    desc13.putObject( idClr, idRGBC, desc14 );
                var idTxtS = charIDToTypeID( "TxtS" );
                desc12.putObject( idTxtS, idTxtS, desc13 );
            var idTxtt = charIDToTypeID( "Txtt" );
            list2.putObject( idTxtt, desc12 );
        desc4.putList( idTxtt, list2 );
        var idparagraphStyleRange = stringIDToTypeID( "paragraphStyleRange" );
            var list3 = new ActionList();
                var desc15 = new ActionDescriptor();
                var idFrom = charIDToTypeID( "From" );
                desc15.putInteger( idFrom, 0 );
                var idT = charIDToTypeID( "T   " );
                desc15.putInteger( idT, maxString );
                var idparagraphStyle = stringIDToTypeID( "paragraphStyle" );
                    var desc16 = new ActionDescriptor();
                    var idstyleSheetHasParent = stringIDToTypeID( "styleSheetHasParent" );
                    desc16.putBoolean( idstyleSheetHasParent, true );
                    var idAlgn = charIDToTypeID( "Algn" );
                    var idAlg = charIDToTypeID( "Alg " );
                    var idRght = charIDToTypeID( "Rght" );
                    desc16.putEnumerated( idAlgn, idAlg, idRght );
                    var iddirectionType = stringIDToTypeID( "directionType" );
                    var iddirectionType = stringIDToTypeID( "directionType" );
                    var iddirLeftToRight = stringIDToTypeID(textAlign);
                    desc16.putEnumerated( iddirectionType, iddirectionType, iddirLeftToRight );
                var idparagraphStyle = stringIDToTypeID( "paragraphStyle" );
                desc15.putObject( idparagraphStyle, idparagraphStyle, desc16 );
            var idparagraphStyleRange = stringIDToTypeID( "paragraphStyleRange" );
            list3.putObject( idparagraphStyleRange, desc15 );
        desc4.putList( idparagraphStyleRange, list3 );
        var idkerningRange = stringIDToTypeID( "kerningRange" );
            var list4 = new ActionList();
        desc4.putList( idkerningRange, list4 );
    var idTxLr = charIDToTypeID( "TxLr" );
    desc3.putObject( idT, idTxLr, desc4 );
executeAction( idsetd, desc3, DialogModes.NO );

layer.textItem.size = size;
}

//------------------------   
   function doesLayerExistUndergroup(group, layer)  {
        for(var layerIdx = 0; layerIdx < group.artLayers.length; layerIdx++) {
                if (group.artLayers[layerIdx].name == layer) {
                    return 1;
                }
        }
        return 0;
    }
//------------------------

    function writeGoalsForPeriod(period) {
        if (period == 0) {
                var period_goal_time = period1_goal_time;        
                var period_goal_teamStat = period1_goal_teamStat;
                var period_goal = period1_goal;
                var period_goal_team = period1_goal_team;
                var period_scorer = period1_scorer;
                var period_ass1 = period1_ass1;
                var period_ass2  = period1_ass2;
        }
        else if (period == 1) {
                var period_goal_time = period2_goal_time;        
                var period_goal_teamStat = period2_goal_teamStat;
                var period_goal = period2_goal;
                var period_goal_team = period2_goal_team;
                var period_scorer = period2_scorer;
                var period_ass1 = period2_ass1;
                var period_ass2  = period2_ass2;
        }
        else if (period == 2) {
                var period_goal_time = period3_goal_time;        
                var period_goal_teamStat = period3_goal_teamStat;
                var period_goal = period3_goal;
                var period_goal_team = period3_goal_team;
                var period_scorer = period3_scorer;
                var period_ass1 = period3_ass1;
                var period_ass2  = period3_ass2;
      }      
      
      
        for (var goalIdx = 0; goalIdx < period_goal.length; goalIdx++) {   
            openPSD(goal);
    
             var mainLayer = app.activeDocument.layerSets;
             var doc = app.activeDocument;
            
            // write info
            var periodIdx = 0;
            
            var layer=mainLayer["Text"].artLayers["Målgörare"];
            doc.activeLayer = layer;
            writePlayer(period_scorer[goalIdx] , 2, true);    
            
            layer=mainLayer["Text"].artLayers["Assisterande 1"];
            doc.activeLayer = layer;
            if (period_ass1[goalIdx] != "N/A") {
                writePlayer(period_ass1[goalIdx] , 2, true);    
                layer.visible = 1;       
            }
            else {
                layer.visible = 0;       
           }
            
            layer=mainLayer["Text"].artLayers["Assisterande 2"];
            doc.activeLayer = layer;
            if (period_ass2[goalIdx] != "N/A") {
                writePlayer(period_ass2[goalIdx] , 2, true);    
                layer.visible = 1;       
            }
            else {
                layer.visible = 0;       
           }
                   
            // find correct goal pic
            // make sure all other layers are hidden berfore using this
            var doc = app.activeDocument;   
           
            if (doesLayerExistUndergroup(mainLayer["Spelarbilder"],period_scorer[goalIdx]) && period_goal_team[goalIdx]== "h") {
                layer=mainLayer["Spelarbilder"].artLayers[period_scorer[goalIdx]];
                doc.activeLayer = layer;
            }
            else {
                layer=mainLayer["Spelarbilder"].artLayers["dummy"];
                doc.activeLayer = layer;        
                
            }
            layer.visble = 1;
            
            layer=mainLayer["Text"].artLayers["Tid för mål"];
            layer.textItem.contents = period_goal_time[goalIdx] + " " + period_goal_teamStat[goalIdx];
            layer=mainLayer["Text"].artLayers["Resultat"];
            layer.textItem.contents = period_goal[goalIdx];
            
            // save as PNG and close
            savePNG(period_goal[goalIdx] + ".png");
            closePSD();
        }
}
//------------------------

  function writeGoalSummaryForPeriod(period) {
        if (period == 0) {
                var period_goal_time = period1_goal_time;        
                var period_goal_teamStat = period1_goal_teamStat;
                var period_goal = period1_goal;
                var period_goal_team = period1_goal_team;
                var period_scorer = period1_scorer;
                var period_ass1 = period1_ass1;
                var period_ass2  = period1_ass2;
        }
        else if (period == 1) {
                var period_goal_time = period2_goal_time;        
                var period_goal_teamStat = period2_goal_teamStat;
                var period_goal = period2_goal;
                var period_goal_team = period2_goal_team;
                var period_scorer = period2_scorer;
                var period_ass1 = period2_ass1;
                var period_ass2  = period2_ass2;
        }
        else if (period == 2) {
                var period_goal_time = period3_goal_time;        
                var period_goal_teamStat = period3_goal_teamStat;
                var period_goal = period3_goal;
                var period_goal_team = period3_goal_team;
                var period_scorer = period3_scorer;
                var period_ass1 = period3_ass1;
                var period_ass2  = period3_ass2;
      }      
      
             openPSD(goalSummary);
    
             var mainLayer = app.activeDocument.layerSets;
             var doc = app.activeDocument;
            
            // write info
            var periodIdx = 0;
            
             var layer=doc.artLayers["Summering peridod X"];
            doc.activeLayer = layer;
            writePlayer("SUMMERING PERIOD " + (period+1) , 10, true);  

			var layer=doc.artLayers["Skott: XX-XX"];
            doc.activeLayer = layer;
            writePlayer("SKOTT:" + homeShots[period] + "-" + awayShots[period]  , 10, true);  

           // show correct away team logo
            // make sure all other layers are hidden berfore using this
            layer=mainLayer["Loggor, höger"].artLayers[awayTeamShort];  
            doc.activeLayer = layer;
            layer.visble = 1; 
            
            layer=mainLayer["Lag"].artLayers["Bortalag"];
            layer.textItem.contents = awayTeamName;
            
             var Teamlayer;
            
             for (var i = 0; i < period_goal.length; i++) {
                    layer=mainLayer["Resultat"].artLayers["Mål " + (i+1)];  
                    doc.activeLayer = layer;
                    layer.visble = 1; 
                    layer.textItem.contents = period_goal[i]; 
                    
                   layer=mainLayer["Tid för mål"].artLayers["Mål " + (i+1)];  
                    doc.activeLayer = layer;
                    layer.visble = 1; 
                    layer.textItem.contents = period_goal_time[i] + " " + period_goal_teamStat[i]; 
                    
                    var leftAligned;
              
                    if (period_goal_team[i]== "h") {
                        leftAligned = true;
                        Teamlayer =mainLayer["Mål/assist - Tranås AIF"];                
                
                    }
                    else {
                        leftAligned = false;
                        Teamlayer =mainLayer["Mål/assist - Bortalag"];
                    }
                 
                 layer=Teamlayer.layers["Mål " + (i+1)].artLayers["Målgörare"];                           
                    doc.activeLayer = layer;    
                     layer.visble = 1; 
                     writePlayer(period_scorer[i], 2, leftAligned);     
                    
                     if (period_ass1[i] != "N/A") {
                        layer=Teamlayer.layers["Mål " + (i+1)].artLayers["Assisterande 1"];
                        doc.activeLayer = layer;    
                        layer.visble = 1; 
                        writePlayer(period_ass1[i] , 2, leftAligned);    
                    }
                
                    if (period_ass2[i] != "N/A") {
                        layer=Teamlayer.layers["Mål " + (i+1)].artLayers["Assisterande 2"];
                        doc.activeLayer = layer;    
                        layer.visble = 1; 
                        writePlayer(period_ass2[i] , 2, leftAligned);    
                    }
             }
             // save as PNG and close
            savePNG("per" + (period+1) + ".png");
            closePSD();
     
         }
     
     
// END  function
        
        
  
    // ----------- Main -----------------

   
    // ---------- Match info ----------

    // open matchinfo psd
   openPSD(matchInfo);
      
    // write info
       var mainLayer = app.activeDocument.layerSets;
    
    var layer=mainLayer["Text"].artLayers["Träningsmatch alt. omgång"];
    layer.textItem.contents = headline;
    
    layer=mainLayer["Text"].artLayers["Datum"];
    layer.textItem.contents = matchDate;
    
    layer=mainLayer["Text"].artLayers["Resultat"];
    layer.textItem.contents = result;
    

    layer=mainLayer["Text"].artLayers["Bortalag"];
    layer.textItem.contents = awayTeamName;
    
    // show correct away team logo
    // make sure all other layers are hidden berfore using this
    layer=mainLayer["Loggor, höger"].artLayers[awayTeamShort];
    var doc = app.activeDocument;    
    doc.activeLayer = layer;
    layer.visble = 1;
    
    // save as PNG and close
    savePNG("info.png");
   
    closePSD();    
    
    // --------- goal templates --------------
    for (var i =  0; i < periods; i++) {
        writeGoalsForPeriod(i) ;        // open goal template, write one goal in a time, loop for every period
        writeGoalSummaryForPeriod(i); // period summary template
    }
    
    
    
    
    
    
    
    
    
    
    
 /*    var period1_goal_time = new Array("02:34", "05:22", "15:43");
    var period1_goal_teamStat = new Array("EQ", "EQ", "PP1");
    var period1_goal= new Array("1-0", "1-1", "2-1");  // testar både hemma och borta mål
    var period1_goal_team = new Array("h", "b", "h");
    var period1_scorer = new Array("5 Albin Torstensson", "12 adam lind", "14 kalle anka"); // 3 mål,. fösta ska identifieras av bild, andra är borta lag, tredje, dummy spelare
    var period1_ass1 = new Array("12 kalle ank", "22 brumsibums", "N/A"); // 1ass på första 2, sedan inte
    var period1_ass2 = new Array("22 braj", "N/A", "N/A"); // 2 ass på första, sedan inga
*/   
    
    
    
    
    // --------------- END main
    
