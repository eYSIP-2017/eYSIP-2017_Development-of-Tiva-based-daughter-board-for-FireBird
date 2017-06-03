<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.3.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Daughterboard">
<packages>
<package name="DAUGHTERBOARD">
<pad name="1" x="-22.86" y="-22.86" drill="1" diameter="1.6764"/>
<pad name="2" x="-22.86" y="-20.32" drill="1" diameter="1.6764"/>
<pad name="3" x="-22.86" y="-17.78" drill="1" diameter="1.6764"/>
<pad name="4" x="-22.86" y="-15.24" drill="1" diameter="1.6764"/>
<pad name="5" x="-22.86" y="-12.7" drill="1" diameter="1.6764"/>
<pad name="6" x="-22.86" y="-10.16" drill="1" diameter="1.6764"/>
<pad name="7" x="-22.86" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="8" x="-22.86" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="9" x="-22.86" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="10" x="-22.86" y="0" drill="1" diameter="1.6764"/>
<pad name="11" x="-22.86" y="2.54" drill="1" diameter="1.6764"/>
<pad name="12" x="-22.86" y="5.08" drill="1" diameter="1.6764"/>
<pad name="13" x="-22.86" y="7.62" drill="1" diameter="1.6764"/>
<pad name="14" x="-22.86" y="10.16" drill="1" diameter="1.6764"/>
<pad name="15" x="-22.86" y="12.7" drill="1" diameter="1.6764"/>
<pad name="16" x="-22.86" y="15.24" drill="1" diameter="1.6764"/>
<pad name="1'" x="-25.4" y="-22.86" drill="1" diameter="1.6764"/>
<pad name="2'" x="-25.4" y="-20.32" drill="1" diameter="1.6764"/>
<pad name="3'" x="-25.4" y="-17.78" drill="1" diameter="1.6764"/>
<pad name="4'" x="-25.4" y="-15.24" drill="1" diameter="1.6764"/>
<pad name="5'" x="-25.4" y="-12.7" drill="1" diameter="1.6764"/>
<pad name="6'" x="-25.4" y="-10.16" drill="1" diameter="1.6764"/>
<pad name="7A" x="-25.4" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="8A" x="-25.4" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="9A" x="-25.4" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="10A" x="-25.4" y="0" drill="1" diameter="1.6764"/>
<pad name="11'" x="-25.4" y="2.54" drill="1" diameter="1.6764"/>
<pad name="12'" x="-25.4" y="5.08" drill="1" diameter="1.6764"/>
<pad name="13'" x="-25.4" y="7.62" drill="1" diameter="1.6764"/>
<pad name="14'" x="-25.4" y="10.16" drill="1" diameter="1.6764"/>
<pad name="15'" x="-25.4" y="12.7" drill="1" diameter="1.6764"/>
<pad name="16'" x="-25.4" y="15.24" drill="1" diameter="1.6764"/>
<pad name="17B" x="-12.7" y="15.24" drill="1" diameter="1.6764"/>
<pad name="18" x="-10.16" y="15.24" drill="1" diameter="1.6764"/>
<pad name="19" x="-7.62" y="15.24" drill="1" diameter="1.6764"/>
<pad name="20" x="-5.08" y="15.24" drill="1" diameter="1.6764"/>
<pad name="21" x="-2.54" y="15.24" drill="1" diameter="1.6764"/>
<pad name="22" x="0" y="15.24" drill="1" diameter="1.6764"/>
<pad name="23" x="2.54" y="15.24" drill="1" diameter="1.6764"/>
<pad name="24" x="5.08" y="15.24" drill="1" diameter="1.6764"/>
<pad name="25" x="7.62" y="15.24" drill="1" diameter="1.6764"/>
<pad name="26" x="10.16" y="15.24" drill="1" diameter="1.6764"/>
<pad name="27" x="12.7" y="15.24" drill="1" diameter="1.6764"/>
<pad name="28" x="15.24" y="15.24" drill="1" diameter="1.6764"/>
<pad name="29" x="17.78" y="15.24" drill="1" diameter="1.6764"/>
<pad name="30" x="20.32" y="15.24" drill="1" diameter="1.6764"/>
<pad name="31" x="22.86" y="15.24" drill="1" diameter="1.6764"/>
<pad name="32" x="25.4" y="15.24" drill="1" diameter="1.6764"/>
<pad name="33" x="27.94" y="15.24" drill="1" diameter="1.6764"/>
<pad name="34" x="30.48" y="15.24" drill="1" diameter="1.6764"/>
<pad name="35" x="33.02" y="15.24" drill="1" diameter="1.6764"/>
<pad name="36" x="35.56" y="15.24" drill="1" diameter="1.6764"/>
<pad name="37" x="38.1" y="15.24" drill="1" diameter="1.6764"/>
<pad name="38" x="40.64" y="15.24" drill="1" diameter="1.6764"/>
<pad name="39" x="43.18" y="15.24" drill="1" diameter="1.6764"/>
<pad name="40" x="45.72" y="15.24" drill="1" diameter="1.6764"/>
<pad name="41" x="48.26" y="15.24" drill="1" diameter="1.6764"/>
<pad name="42" x="50.8" y="15.24" drill="1" diameter="1.6764"/>
<pad name="43" x="53.34" y="15.24" drill="1" diameter="1.6764"/>
<pad name="44" x="55.88" y="15.24" drill="1" diameter="1.6764"/>
<pad name="45" x="58.42" y="15.24" drill="1" diameter="1.6764"/>
<pad name="46" x="60.96" y="15.24" drill="1" diameter="1.6764"/>
<pad name="47" x="63.5" y="15.24" drill="1" diameter="1.6764"/>
<pad name="48" x="66.04" y="15.24" drill="1" diameter="1.6764"/>
<pad name="49" x="68.58" y="15.24" drill="1" diameter="1.6764"/>
<pad name="50" x="71.12" y="15.24" drill="1" diameter="1.6764"/>
<pad name="51" x="73.66" y="15.24" drill="1" diameter="1.6764"/>
<pad name="52" x="76.2" y="15.24" drill="1" diameter="1.6764"/>
<pad name="53" x="78.74" y="15.24" drill="1" diameter="1.6764"/>
<pad name="54" x="81.28" y="15.24" drill="1" diameter="1.6764"/>
<pad name="55" x="83.82" y="15.24" drill="1" diameter="1.6764"/>
<pad name="17A" x="-12.7" y="17.78" drill="1" diameter="1.6764"/>
<pad name="18'" x="-10.16" y="17.78" drill="1" diameter="1.6764"/>
<pad name="19'" x="-7.62" y="17.78" drill="1" diameter="1.6764"/>
<pad name="20A" x="-5.08" y="17.78" drill="1" diameter="1.6764"/>
<pad name="21A" x="-2.54" y="17.78" drill="1" diameter="1.6764"/>
<pad name="22'" x="0" y="17.78" drill="1" diameter="1.6764"/>
<pad name="23'" x="2.54" y="17.78" drill="1" diameter="1.6764"/>
<pad name="24'" x="5.08" y="17.78" drill="1" diameter="1.6764"/>
<pad name="25'" x="7.62" y="17.78" drill="1" diameter="1.6764"/>
<pad name="26'" x="10.16" y="17.78" drill="1" diameter="1.6764"/>
<pad name="27'" x="12.7" y="17.78" drill="1" diameter="1.6764"/>
<pad name="28'" x="15.24" y="17.78" drill="1" diameter="1.6764"/>
<pad name="29'" x="17.78" y="17.78" drill="1" diameter="1.6764"/>
<pad name="30'" x="20.32" y="17.78" drill="1" diameter="1.6764"/>
<pad name="31'" x="22.86" y="17.78" drill="1" diameter="1.6764"/>
<pad name="32'" x="25.4" y="17.78" drill="1" diameter="1.6764"/>
<pad name="33'" x="27.94" y="17.78" drill="1" diameter="1.6764"/>
<pad name="34'" x="30.48" y="17.78" drill="1" diameter="1.6764"/>
<pad name="35A" x="33.02" y="17.78" drill="1" diameter="1.6764"/>
<pad name="36'" x="35.56" y="17.78" drill="1" diameter="1.6764"/>
<pad name="37'" x="38.1" y="17.78" drill="1" diameter="1.6764"/>
<pad name="38'" x="40.64" y="17.78" drill="1" diameter="1.6764"/>
<pad name="39'" x="43.18" y="17.78" drill="1" diameter="1.6764"/>
<pad name="40'" x="45.72" y="17.78" drill="1" diameter="1.6764"/>
<pad name="41'" x="48.26" y="17.78" drill="1" diameter="1.6764"/>
<pad name="42'" x="50.8" y="17.78" drill="1" diameter="1.6764"/>
<pad name="43'" x="53.34" y="17.78" drill="1" diameter="1.6764"/>
<pad name="44'" x="55.88" y="17.78" drill="1" diameter="1.6764"/>
<pad name="45'" x="58.42" y="17.78" drill="1" diameter="1.6764"/>
<pad name="46'" x="60.96" y="17.78" drill="1" diameter="1.6764"/>
<pad name="47'" x="63.5" y="17.78" drill="1" diameter="1.6764"/>
<pad name="48'" x="66.04" y="17.78" drill="1" diameter="1.6764"/>
<pad name="49'" x="68.58" y="17.78" drill="1" diameter="1.6764"/>
<pad name="50'" x="71.12" y="17.78" drill="1" diameter="1.6764"/>
<pad name="51'" x="73.66" y="17.78" drill="1" diameter="1.6764"/>
<pad name="52'" x="76.2" y="17.78" drill="1" diameter="1.6764"/>
<pad name="53'" x="78.74" y="17.78" drill="1" diameter="1.6764"/>
<pad name="54'" x="81.28" y="17.78" drill="1" diameter="1.6764"/>
<pad name="55'" x="83.82" y="17.78" drill="1" diameter="1.6764"/>
<pad name="57" x="88.9" y="15.24" drill="1" diameter="1.6764"/>
<pad name="58" x="88.9" y="12.7" drill="1" diameter="1.6764"/>
<pad name="59" x="88.9" y="10.16" drill="1" diameter="1.6764"/>
<pad name="60" x="88.9" y="7.62" drill="1" diameter="1.6764"/>
<pad name="61" x="88.9" y="5.08" drill="1" diameter="1.6764"/>
<pad name="62" x="88.9" y="2.54" drill="1" diameter="1.6764"/>
<pad name="63" x="88.9" y="0" drill="1" diameter="1.6764"/>
<pad name="64" x="88.9" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="65" x="88.9" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="66" x="88.9" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="67" x="88.9" y="-10.16" drill="1" diameter="1.6764"/>
<pad name="68" x="88.9" y="-12.7" drill="1" diameter="1.6764"/>
<pad name="69" x="88.9" y="-15.24" drill="1" diameter="1.6764"/>
<pad name="70" x="88.9" y="-17.78" drill="1" diameter="1.6764"/>
<pad name="71" x="88.9" y="-20.32" drill="1" diameter="1.6764"/>
<pad name="72" x="88.9" y="-22.86" drill="1" diameter="1.6764"/>
<pad name="73" x="88.9" y="-25.4" drill="1" diameter="1.6764"/>
<pad name="74" x="88.9" y="-27.94" drill="1" diameter="1.6764"/>
<pad name="57A" x="91.44" y="15.24" drill="1" diameter="1.6764"/>
<pad name="58A" x="91.44" y="12.7" drill="1" diameter="1.6764"/>
<pad name="59A" x="91.44" y="10.16" drill="1" diameter="1.6764"/>
<pad name="60A" x="91.44" y="7.62" drill="1" diameter="1.6764"/>
<pad name="61'" x="91.44" y="5.08" drill="1" diameter="1.6764"/>
<pad name="62'" x="91.44" y="2.54" drill="1" diameter="1.6764"/>
<pad name="63'" x="91.44" y="0" drill="1" diameter="1.6764"/>
<pad name="64'" x="91.44" y="-2.54" drill="1" diameter="1.6764"/>
<pad name="65'" x="91.44" y="-5.08" drill="1" diameter="1.6764"/>
<pad name="66'" x="91.44" y="-7.62" drill="1" diameter="1.6764"/>
<pad name="67'" x="91.44" y="-10.16" drill="1" diameter="1.6764"/>
<pad name="68'" x="91.44" y="-12.7" drill="1" diameter="1.6764"/>
<pad name="69'" x="91.44" y="-15.24" drill="1" diameter="1.6764"/>
<pad name="70'" x="91.44" y="-17.78" drill="1" diameter="1.6764"/>
<pad name="71'" x="91.44" y="-20.32" drill="1" diameter="1.6764"/>
<pad name="72'" x="91.44" y="-22.86" drill="1" diameter="1.6764"/>
<pad name="73'" x="91.44" y="-25.4" drill="1" diameter="1.6764"/>
<pad name="74'" x="91.44" y="-27.94" drill="1" diameter="1.6764"/>
<wire x1="-26.67" y1="16.51" x2="-21.59" y2="16.51" width="0.127" layer="21"/>
<wire x1="-21.59" y1="16.51" x2="-21.59" y2="-24.13" width="0.127" layer="21"/>
<wire x1="-21.59" y1="-24.13" x2="-26.67" y2="-24.13" width="0.127" layer="21"/>
<wire x1="-26.67" y1="-24.13" x2="-26.67" y2="16.51" width="0.127" layer="21"/>
<wire x1="-13.97" y1="19.05" x2="-13.97" y2="13.97" width="0.127" layer="21"/>
<wire x1="-13.97" y1="13.97" x2="85.09" y2="13.97" width="0.127" layer="21"/>
<wire x1="85.09" y1="13.97" x2="85.09" y2="19.05" width="0.127" layer="21"/>
<wire x1="85.09" y1="19.05" x2="-13.97" y2="19.05" width="0.127" layer="21"/>
<wire x1="87.63" y1="16.51" x2="92.71" y2="16.51" width="0.127" layer="21"/>
<wire x1="92.71" y1="16.51" x2="92.71" y2="-29.21" width="0.127" layer="21"/>
<wire x1="92.71" y1="-29.21" x2="87.63" y2="-29.21" width="0.127" layer="21"/>
<wire x1="87.63" y1="-29.21" x2="87.63" y2="16.51" width="0.127" layer="21"/>
<text x="-27.1526" y="-23.0378" size="1.27" layer="21" rot="R90">Header 16x2</text>
<text x="-13.843" y="19.5834" size="1.27" layer="21">Header 39x2</text>
<text x="93.3196" y="14.859" size="1.27" layer="21" rot="R270">Header 18x2</text>
</package>
</packages>
<symbols>
<symbol name="FIREBIRDV_DB">
<description>This is the header pin schematic for daughter board of firebird V.
Here the pin and its prime have to be shorted(i.e 1 and 1' have to be shorted)</description>
<wire x1="-63.5" y1="20.32" x2="-63.5" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-63.5" y1="-22.86" x2="-76.2" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-76.2" y1="-22.86" x2="-76.2" y2="20.32" width="0.254" layer="94"/>
<pin name="1" x="-60.96" y="-20.32" length="short" direction="out" rot="R180"/>
<pin name="2" x="-60.96" y="-17.78" length="short" direction="out" rot="R180"/>
<pin name="3" x="-60.96" y="-15.24" length="short" direction="out" rot="R180"/>
<pin name="4" x="-60.96" y="-12.7" length="short" direction="out" rot="R180"/>
<pin name="5" x="-60.96" y="-10.16" length="short" direction="out" rot="R180"/>
<pin name="6" x="-60.96" y="-7.62" length="short" direction="out" rot="R180"/>
<pin name="7" x="-60.96" y="-5.08" length="short" direction="out" rot="R180"/>
<pin name="8" x="-60.96" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="9" x="-60.96" y="0" length="short" direction="out" rot="R180"/>
<pin name="10" x="-60.96" y="2.54" length="short" direction="out" rot="R180"/>
<pin name="11" x="-60.96" y="5.08" length="short" direction="out" rot="R180"/>
<pin name="12" x="-60.96" y="7.62" length="short" direction="out" rot="R180"/>
<pin name="13" x="-60.96" y="10.16" length="short" direction="out" rot="R180"/>
<pin name="14" x="-60.96" y="12.7" length="short" direction="out" rot="R180"/>
<pin name="15" x="-60.96" y="15.24" length="short" direction="out" rot="R180"/>
<pin name="16" x="-60.96" y="17.78" length="short" direction="out" rot="R180"/>
<wire x1="-76.2" y1="20.32" x2="-63.5" y2="20.32" width="0.254" layer="94"/>
<pin name="1'" x="-78.74" y="-20.32" length="short" direction="out"/>
<pin name="2'" x="-78.74" y="-17.78" length="short" direction="out"/>
<pin name="3'" x="-78.74" y="-15.24" length="short" direction="out"/>
<pin name="4'" x="-78.74" y="-12.7" length="short" direction="out"/>
<pin name="5'" x="-78.74" y="-10.16" length="short" direction="out"/>
<pin name="6'" x="-78.74" y="-7.62" length="short" direction="out"/>
<pin name="7A" x="-78.74" y="-5.08" length="short" direction="out"/>
<pin name="8A" x="-78.74" y="-2.54" length="short" direction="out"/>
<pin name="9A" x="-78.74" y="0" length="short" direction="out"/>
<pin name="10A" x="-78.74" y="2.54" length="short" direction="out"/>
<pin name="11'" x="-78.74" y="5.08" length="short" direction="out"/>
<pin name="12'" x="-78.74" y="7.62" length="short" direction="out"/>
<pin name="13'" x="-78.74" y="10.16" length="short" direction="out"/>
<pin name="14'" x="-78.74" y="12.7" length="short" direction="out"/>
<pin name="15'" x="-78.74" y="15.24" length="short" direction="out"/>
<pin name="16'" x="-78.74" y="17.78" length="short" direction="out"/>
<wire x1="-58.42" y1="40.64" x2="-58.42" y2="27.94" width="0.254" layer="94"/>
<wire x1="-58.42" y1="27.94" x2="43.18" y2="27.94" width="0.254" layer="94"/>
<wire x1="43.18" y1="27.94" x2="43.18" y2="40.64" width="0.254" layer="94"/>
<wire x1="43.18" y1="40.64" x2="-58.42" y2="40.64" width="0.254" layer="94"/>
<pin name="17B" x="-55.88" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="18" x="-53.34" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="19" x="-50.8" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="20" x="-48.26" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="21" x="-45.72" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="22" x="-43.18" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="23" x="-40.64" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="24" x="-38.1" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="25" x="-35.56" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="26" x="-33.02" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="27" x="-30.48" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="28" x="-27.94" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="29" x="-25.4" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="30" x="-22.86" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="31" x="-20.32" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="32" x="-17.78" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="33" x="-15.24" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="34" x="-12.7" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="35" x="-10.16" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="36" x="-7.62" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="37" x="-5.08" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="38" x="-2.54" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="39" x="0" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="40" x="2.54" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="41" x="5.08" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="42" x="7.62" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="43" x="10.16" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="44" x="12.7" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="45" x="15.24" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="46" x="17.78" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="47" x="20.32" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="48" x="22.86" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="49" x="25.4" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="50" x="27.94" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="51" x="30.48" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="52" x="33.02" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="53" x="35.56" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="54" x="38.1" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="55" x="40.64" y="25.4" length="short" direction="out" rot="R90"/>
<pin name="17A" x="-55.88" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="18'" x="-53.34" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="19'" x="-50.8" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="20A" x="-48.26" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="21A" x="-45.72" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="22'" x="-43.18" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="23'" x="-40.64" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="24'" x="-38.1" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="25'" x="-35.56" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="26'" x="-33.02" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="27'" x="-30.48" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="28'" x="-27.94" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="29'" x="-25.4" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="30'" x="-22.86" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="31'" x="-20.32" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="32'" x="-17.78" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="33'" x="-15.24" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="34'" x="-12.7" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="35A" x="-10.16" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="36'" x="-7.62" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="37'" x="-5.08" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="38'" x="-2.54" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="39'" x="0" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="40'" x="2.54" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="41'" x="5.08" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="42'" x="7.62" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="43'" x="10.16" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="44'" x="12.7" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="45'" x="15.24" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="46'" x="17.78" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="47'" x="20.32" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="48'" x="22.86" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="49'" x="25.4" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="50'" x="27.94" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="51'" x="30.48" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="52'" x="33.02" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="53'" x="35.56" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="54'" x="38.1" y="43.18" length="short" direction="out" rot="R270"/>
<pin name="55'" x="40.64" y="43.18" length="short" direction="out" rot="R270"/>
<wire x1="48.26" y1="20.32" x2="60.96" y2="20.32" width="0.254" layer="94"/>
<wire x1="60.96" y1="20.32" x2="60.96" y2="-27.94" width="0.254" layer="94"/>
<wire x1="60.96" y1="-27.94" x2="48.26" y2="-27.94" width="0.254" layer="94"/>
<wire x1="48.26" y1="-27.94" x2="48.26" y2="20.32" width="0.254" layer="94"/>
<pin name="57" x="45.72" y="17.78" length="short" direction="out"/>
<pin name="58" x="45.72" y="15.24" length="short" direction="out"/>
<pin name="59" x="45.72" y="12.7" length="short" direction="out"/>
<pin name="60" x="45.72" y="10.16" length="short" direction="out"/>
<pin name="61" x="45.72" y="7.62" length="short" direction="out"/>
<pin name="62" x="45.72" y="5.08" length="short" direction="out"/>
<pin name="63" x="45.72" y="2.54" length="short" direction="out"/>
<pin name="64" x="45.72" y="0" length="short" direction="out"/>
<pin name="65" x="45.72" y="-2.54" length="short" direction="out"/>
<pin name="66" x="45.72" y="-5.08" length="short" direction="out"/>
<pin name="67" x="45.72" y="-7.62" length="short" direction="out"/>
<pin name="68" x="45.72" y="-10.16" length="short" direction="out"/>
<pin name="69" x="45.72" y="-12.7" length="short" direction="out"/>
<pin name="70" x="45.72" y="-15.24" length="short" direction="out"/>
<pin name="71" x="45.72" y="-17.78" length="short" direction="out"/>
<pin name="72" x="45.72" y="-20.32" length="short" direction="out"/>
<pin name="73" x="45.72" y="-22.86" length="short" direction="out"/>
<pin name="74" x="45.72" y="-25.4" length="short" direction="out"/>
<pin name="57A" x="63.5" y="17.78" length="short" direction="out" rot="R180"/>
<pin name="58A" x="63.5" y="15.24" length="short" direction="out" rot="R180"/>
<pin name="59A" x="63.5" y="12.7" length="short" direction="out" rot="R180"/>
<pin name="60A" x="63.5" y="10.16" length="short" direction="out" rot="R180"/>
<pin name="61'" x="63.5" y="7.62" length="short" direction="out" rot="R180"/>
<pin name="62'" x="63.5" y="5.08" length="short" direction="out" rot="R180"/>
<pin name="63'" x="63.5" y="2.54" length="short" direction="out" rot="R180"/>
<pin name="64'" x="63.5" y="0" length="short" direction="out" rot="R180"/>
<pin name="65'" x="63.5" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="66'" x="63.5" y="-5.08" length="short" direction="out" rot="R180"/>
<pin name="67'" x="63.5" y="-7.62" length="short" direction="out" rot="R180"/>
<pin name="68'" x="63.5" y="-10.16" length="short" direction="out" rot="R180"/>
<pin name="69'" x="63.5" y="-12.7" length="short" direction="out" rot="R180"/>
<pin name="70'" x="63.5" y="-15.24" length="short" direction="out" rot="R180"/>
<pin name="71'" x="63.5" y="-17.78" length="short" direction="out" rot="R180"/>
<pin name="72'" x="63.5" y="-20.32" length="short" direction="out" rot="R180"/>
<pin name="73'" x="63.5" y="-22.86" length="short" direction="out" rot="R180"/>
<pin name="74'" x="63.5" y="-25.4" length="short" direction="out" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DAUGHTERBOARD">
<gates>
<gate name="G$1" symbol="FIREBIRDV_DB" x="7.62" y="-5.08"/>
</gates>
<devices>
<device name="DAUGHTERBOARD" package="DAUGHTERBOARD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="1'" pad="1'"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="10A" pad="10A"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="11'" pad="11'"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="12'" pad="12'"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="13'" pad="13'"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="14'" pad="14'"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="15'" pad="15'"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="16'" pad="16'"/>
<connect gate="G$1" pin="17A" pad="17A"/>
<connect gate="G$1" pin="17B" pad="17B"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="18'" pad="18'"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="19'" pad="19'"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="2'" pad="2'"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="20A" pad="20A"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="21A" pad="21A"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="22'" pad="22'"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="23'" pad="23'"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="24'" pad="24'"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="25'" pad="25'"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="26'" pad="26'"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="27'" pad="27'"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="28'" pad="28'"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="29'" pad="29'"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="3'" pad="3'"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="30'" pad="30'"/>
<connect gate="G$1" pin="31" pad="31"/>
<connect gate="G$1" pin="31'" pad="31'"/>
<connect gate="G$1" pin="32" pad="32"/>
<connect gate="G$1" pin="32'" pad="32'"/>
<connect gate="G$1" pin="33" pad="33"/>
<connect gate="G$1" pin="33'" pad="33'"/>
<connect gate="G$1" pin="34" pad="34"/>
<connect gate="G$1" pin="34'" pad="34'"/>
<connect gate="G$1" pin="35" pad="35"/>
<connect gate="G$1" pin="35A" pad="35A"/>
<connect gate="G$1" pin="36" pad="36"/>
<connect gate="G$1" pin="36'" pad="36'"/>
<connect gate="G$1" pin="37" pad="37"/>
<connect gate="G$1" pin="37'" pad="37'"/>
<connect gate="G$1" pin="38" pad="38"/>
<connect gate="G$1" pin="38'" pad="38'"/>
<connect gate="G$1" pin="39" pad="39"/>
<connect gate="G$1" pin="39'" pad="39'"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="4'" pad="4'"/>
<connect gate="G$1" pin="40" pad="40"/>
<connect gate="G$1" pin="40'" pad="40'"/>
<connect gate="G$1" pin="41" pad="41"/>
<connect gate="G$1" pin="41'" pad="41'"/>
<connect gate="G$1" pin="42" pad="42"/>
<connect gate="G$1" pin="42'" pad="42'"/>
<connect gate="G$1" pin="43" pad="43"/>
<connect gate="G$1" pin="43'" pad="43'"/>
<connect gate="G$1" pin="44" pad="44"/>
<connect gate="G$1" pin="44'" pad="44'"/>
<connect gate="G$1" pin="45" pad="45"/>
<connect gate="G$1" pin="45'" pad="45'"/>
<connect gate="G$1" pin="46" pad="46"/>
<connect gate="G$1" pin="46'" pad="46'"/>
<connect gate="G$1" pin="47" pad="47"/>
<connect gate="G$1" pin="47'" pad="47'"/>
<connect gate="G$1" pin="48" pad="48"/>
<connect gate="G$1" pin="48'" pad="48'"/>
<connect gate="G$1" pin="49" pad="49"/>
<connect gate="G$1" pin="49'" pad="49'"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="5'" pad="5'"/>
<connect gate="G$1" pin="50" pad="50"/>
<connect gate="G$1" pin="50'" pad="50'"/>
<connect gate="G$1" pin="51" pad="51"/>
<connect gate="G$1" pin="51'" pad="51'"/>
<connect gate="G$1" pin="52" pad="52"/>
<connect gate="G$1" pin="52'" pad="52'"/>
<connect gate="G$1" pin="53" pad="53"/>
<connect gate="G$1" pin="53'" pad="53'"/>
<connect gate="G$1" pin="54" pad="54"/>
<connect gate="G$1" pin="54'" pad="54'"/>
<connect gate="G$1" pin="55" pad="55"/>
<connect gate="G$1" pin="55'" pad="55'"/>
<connect gate="G$1" pin="57" pad="57"/>
<connect gate="G$1" pin="57A" pad="57A"/>
<connect gate="G$1" pin="58" pad="58"/>
<connect gate="G$1" pin="58A" pad="58A"/>
<connect gate="G$1" pin="59" pad="59"/>
<connect gate="G$1" pin="59A" pad="59A"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="6'" pad="6'"/>
<connect gate="G$1" pin="60" pad="60"/>
<connect gate="G$1" pin="60A" pad="60A"/>
<connect gate="G$1" pin="61" pad="61"/>
<connect gate="G$1" pin="61'" pad="61'"/>
<connect gate="G$1" pin="62" pad="62"/>
<connect gate="G$1" pin="62'" pad="62'"/>
<connect gate="G$1" pin="63" pad="63"/>
<connect gate="G$1" pin="63'" pad="63'"/>
<connect gate="G$1" pin="64" pad="64"/>
<connect gate="G$1" pin="64'" pad="64'"/>
<connect gate="G$1" pin="65" pad="65"/>
<connect gate="G$1" pin="65'" pad="65'"/>
<connect gate="G$1" pin="66" pad="66"/>
<connect gate="G$1" pin="66'" pad="66'"/>
<connect gate="G$1" pin="67" pad="67"/>
<connect gate="G$1" pin="67'" pad="67'"/>
<connect gate="G$1" pin="68" pad="68"/>
<connect gate="G$1" pin="68'" pad="68'"/>
<connect gate="G$1" pin="69" pad="69"/>
<connect gate="G$1" pin="69'" pad="69'"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="70" pad="70"/>
<connect gate="G$1" pin="70'" pad="70'"/>
<connect gate="G$1" pin="71" pad="71"/>
<connect gate="G$1" pin="71'" pad="71'"/>
<connect gate="G$1" pin="72" pad="72"/>
<connect gate="G$1" pin="72'" pad="72'"/>
<connect gate="G$1" pin="73" pad="73"/>
<connect gate="G$1" pin="73'" pad="73'"/>
<connect gate="G$1" pin="74" pad="74"/>
<connect gate="G$1" pin="74'" pad="74'"/>
<connect gate="G$1" pin="7A" pad="7A"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="8A" pad="8A"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="9A" pad="9A"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SMD_TIVA_LAUNCHPAD">
<packages>
<package name="TIVA_LAUNCHPAD">
<wire x1="-17.78" y1="12.7" x2="-17.78" y2="-15.24" width="0.127" layer="21"/>
<wire x1="-17.78" y1="-15.24" x2="-10.16" y2="-15.24" width="0.127" layer="21"/>
<wire x1="-10.16" y1="-15.24" x2="-10.16" y2="12.7" width="0.127" layer="21"/>
<wire x1="-10.16" y1="12.7" x2="-17.78" y2="12.7" width="0.127" layer="21"/>
<wire x1="25.4" y1="12.7" x2="25.4" y2="-15.24" width="0.127" layer="21"/>
<wire x1="25.4" y1="-15.24" x2="33.02" y2="-15.24" width="0.127" layer="21"/>
<wire x1="33.02" y1="-15.24" x2="33.02" y2="12.7" width="0.127" layer="21"/>
<wire x1="33.02" y1="12.7" x2="25.4" y2="12.7" width="0.127" layer="21"/>
<wire x1="-17.78" y1="40.64" x2="-17.78" y2="-25.4" width="0.127" layer="21"/>
<wire x1="-17.78" y1="-25.4" x2="33.02" y2="-25.4" width="0.127" layer="21"/>
<wire x1="33.02" y1="-25.4" x2="33.02" y2="40.64" width="0.127" layer="21"/>
<wire x1="33.02" y1="40.64" x2="-17.78" y2="40.64" width="0.127" layer="21"/>
<text x="-17.78" y="43.18" size="1.27" layer="21">TIVA LAUNCHPAD</text>
<smd name="3.3V" x="-16.51" y="10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB5" x="-16.51" y="7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB0" x="-16.51" y="5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB1" x="-16.51" y="2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE4" x="-16.51" y="0" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE5" x="-16.51" y="-2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB4" x="-16.51" y="-5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA5" x="-16.51" y="-7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA6" x="-16.51" y="-10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA7" x="-16.51" y="-12.7" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="VBUS" x="-11.43" y="10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="GND" x="-11.43" y="7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD0" x="-11.43" y="5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD1" x="-11.43" y="2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD2" x="-11.43" y="0" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD3" x="-11.43" y="-2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE1" x="-11.43" y="-5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE2" x="-11.43" y="-7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE3" x="-11.43" y="-10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PF1" x="-11.43" y="-12.7" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PF2" x="26.67" y="10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PF3" x="26.67" y="7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB3" x="26.67" y="5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PC4" x="26.67" y="2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PC5" x="26.67" y="0" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PC6" x="26.67" y="-2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PC7" x="26.67" y="-5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD6" x="26.67" y="-7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PD7" x="26.67" y="-10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PF4" x="26.67" y="-12.7" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA2" x="31.75" y="-12.7" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA3" x="31.75" y="-10.16" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PA4" x="31.75" y="-7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB6" x="31.75" y="-5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB7" x="31.75" y="-2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="RST" x="31.75" y="0" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PF0" x="31.75" y="2.54" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PE0" x="31.75" y="5.08" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="PB2" x="31.75" y="7.62" dx="2.1844" dy="1.0668" layer="1"/>
<smd name="GND'" x="31.75" y="10.16" dx="2.1844" dy="1.0668" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="TIVA_LAUNCHPAD">
<wire x1="-22.86" y1="25.4" x2="-22.86" y2="-30.48" width="0.254" layer="94"/>
<wire x1="-22.86" y1="-30.48" x2="17.78" y2="-30.48" width="0.254" layer="94"/>
<wire x1="17.78" y1="-30.48" x2="17.78" y2="25.4" width="0.254" layer="94"/>
<wire x1="17.78" y1="25.4" x2="-22.86" y2="25.4" width="0.254" layer="94"/>
<pin name="3.3V" x="-27.94" y="22.86" length="middle"/>
<pin name="PB5" x="-27.94" y="20.32" length="middle"/>
<pin name="PB0" x="-27.94" y="17.78" length="middle"/>
<pin name="PB1" x="-27.94" y="15.24" length="middle"/>
<pin name="PE4" x="-27.94" y="12.7" length="middle"/>
<pin name="PE5" x="-27.94" y="10.16" length="middle"/>
<pin name="PB4" x="-27.94" y="7.62" length="middle"/>
<pin name="PA5" x="-27.94" y="5.08" length="middle"/>
<pin name="PA6" x="-27.94" y="2.54" length="middle"/>
<pin name="PA7" x="-27.94" y="0" length="middle"/>
<pin name="VBUS" x="-27.94" y="-2.54" length="middle"/>
<pin name="GND" x="-27.94" y="-5.08" length="middle"/>
<pin name="PD0" x="-27.94" y="-7.62" length="middle"/>
<pin name="PD1" x="-27.94" y="-10.16" length="middle"/>
<pin name="PD2" x="-27.94" y="-12.7" length="middle"/>
<pin name="PD3" x="-27.94" y="-15.24" length="middle"/>
<pin name="PE1" x="-27.94" y="-17.78" length="middle"/>
<pin name="PE2" x="-27.94" y="-20.32" length="middle"/>
<pin name="PE3" x="-27.94" y="-22.86" length="middle"/>
<pin name="PF1" x="-27.94" y="-25.4" length="middle"/>
<pin name="GND'" x="22.86" y="22.86" length="middle" rot="R180"/>
<pin name="PB2" x="22.86" y="20.32" length="middle" rot="R180"/>
<pin name="PE0" x="22.86" y="17.78" length="middle" rot="R180"/>
<pin name="PF0" x="22.86" y="15.24" length="middle" rot="R180"/>
<pin name="RST" x="22.86" y="12.7" length="middle" rot="R180"/>
<pin name="PB7" x="22.86" y="10.16" length="middle" rot="R180"/>
<pin name="PB6" x="22.86" y="7.62" length="middle" rot="R180"/>
<pin name="PA4" x="22.86" y="5.08" length="middle" rot="R180"/>
<pin name="PA3" x="22.86" y="2.54" length="middle" rot="R180"/>
<pin name="PA2" x="22.86" y="0" length="middle" rot="R180"/>
<pin name="PF2" x="22.86" y="-2.54" length="middle" rot="R180"/>
<pin name="PF3" x="22.86" y="-5.08" length="middle" rot="R180"/>
<pin name="PB3" x="22.86" y="-7.62" length="middle" rot="R180"/>
<pin name="PC4" x="22.86" y="-10.16" length="middle" rot="R180"/>
<pin name="PC5" x="22.86" y="-12.7" length="middle" rot="R180"/>
<pin name="PC6" x="22.86" y="-15.24" length="middle" rot="R180"/>
<pin name="PC7" x="22.86" y="-17.78" length="middle" rot="R180"/>
<pin name="PD6" x="22.86" y="-20.32" length="middle" rot="R180"/>
<pin name="PD7" x="22.86" y="-22.86" length="middle" rot="R180"/>
<pin name="PF4" x="22.86" y="-25.4" length="middle" rot="R180"/>
<text x="-12.7" y="2.54" size="1.778" layer="94">TIVA LAUNCHPAD</text>
<text x="-10.16" y="-2.54" size="1.778" layer="94">tm4c123gh6pm</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="TIVA_LAUNCHPAD">
<gates>
<gate name="G$1" symbol="TIVA_LAUNCHPAD" x="0" y="2.54"/>
</gates>
<devices>
<device name="TIVA_LAUNCHPAD" package="TIVA_LAUNCHPAD">
<connects>
<connect gate="G$1" pin="3.3V" pad="3.3V"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND'" pad="GND'"/>
<connect gate="G$1" pin="PA2" pad="PA2"/>
<connect gate="G$1" pin="PA3" pad="PA3"/>
<connect gate="G$1" pin="PA4" pad="PA4"/>
<connect gate="G$1" pin="PA5" pad="PA5"/>
<connect gate="G$1" pin="PA6" pad="PA6"/>
<connect gate="G$1" pin="PA7" pad="PA7"/>
<connect gate="G$1" pin="PB0" pad="PB0"/>
<connect gate="G$1" pin="PB1" pad="PB1"/>
<connect gate="G$1" pin="PB2" pad="PB2"/>
<connect gate="G$1" pin="PB3" pad="PB3"/>
<connect gate="G$1" pin="PB4" pad="PB4"/>
<connect gate="G$1" pin="PB5" pad="PB5"/>
<connect gate="G$1" pin="PB6" pad="PB6"/>
<connect gate="G$1" pin="PB7" pad="PB7"/>
<connect gate="G$1" pin="PC4" pad="PC4"/>
<connect gate="G$1" pin="PC5" pad="PC5"/>
<connect gate="G$1" pin="PC6" pad="PC6"/>
<connect gate="G$1" pin="PC7" pad="PC7"/>
<connect gate="G$1" pin="PD0" pad="PD0"/>
<connect gate="G$1" pin="PD1" pad="PD1"/>
<connect gate="G$1" pin="PD2" pad="PD2"/>
<connect gate="G$1" pin="PD3" pad="PD3"/>
<connect gate="G$1" pin="PD6" pad="PD6"/>
<connect gate="G$1" pin="PD7" pad="PD7"/>
<connect gate="G$1" pin="PE0" pad="PE0"/>
<connect gate="G$1" pin="PE1" pad="PE1"/>
<connect gate="G$1" pin="PE2" pad="PE2"/>
<connect gate="G$1" pin="PE3" pad="PE3"/>
<connect gate="G$1" pin="PE4" pad="PE4"/>
<connect gate="G$1" pin="PE5" pad="PE5"/>
<connect gate="G$1" pin="PF0" pad="PF0"/>
<connect gate="G$1" pin="PF1" pad="PF1"/>
<connect gate="G$1" pin="PF2" pad="PF2"/>
<connect gate="G$1" pin="PF3" pad="PF3"/>
<connect gate="G$1" pin="PF4" pad="PF4"/>
<connect gate="G$1" pin="RST" pad="RST"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="Daughterboard" deviceset="DAUGHTERBOARD" device="DAUGHTERBOARD"/>
<part name="U$2" library="SMD_TIVA_LAUNCHPAD" deviceset="TIVA_LAUNCHPAD" device="TIVA_LAUNCHPAD"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="88.9" y="55.88"/>
<instance part="U$2" gate="G$1" x="78.74" y="10.16"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="1'"/>
<pinref part="U$1" gate="G$1" pin="1"/>
<wire x1="10.16" y1="35.56" x2="27.94" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="2'"/>
<pinref part="U$1" gate="G$1" pin="2"/>
<wire x1="10.16" y1="38.1" x2="27.94" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3'"/>
<pinref part="U$1" gate="G$1" pin="3"/>
<wire x1="10.16" y1="40.64" x2="27.94" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="4'"/>
<pinref part="U$1" gate="G$1" pin="4"/>
<wire x1="10.16" y1="43.18" x2="27.94" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="5'"/>
<pinref part="U$1" gate="G$1" pin="5"/>
<wire x1="10.16" y1="45.72" x2="27.94" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="6'"/>
<pinref part="U$1" gate="G$1" pin="6"/>
<wire x1="10.16" y1="48.26" x2="27.94" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="12" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="12'"/>
<pinref part="U$1" gate="G$1" pin="12"/>
<wire x1="10.16" y1="63.5" x2="27.94" y2="63.5" width="0.1524" layer="91"/>
<wire x1="27.94" y1="63.5" x2="33.02" y2="63.5" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PB5"/>
<wire x1="50.8" y1="30.48" x2="45.72" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="13" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="13'"/>
<pinref part="U$1" gate="G$1" pin="13"/>
<wire x1="10.16" y1="66.04" x2="27.94" y2="66.04" width="0.1524" layer="91"/>
<wire x1="27.94" y1="66.04" x2="33.02" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PB1"/>
<wire x1="50.8" y1="25.4" x2="45.72" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="14" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="14'"/>
<pinref part="U$1" gate="G$1" pin="14"/>
<wire x1="10.16" y1="68.58" x2="27.94" y2="68.58" width="0.1524" layer="91"/>
<wire x1="27.94" y1="68.58" x2="33.02" y2="68.58" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PB0"/>
<wire x1="50.8" y1="27.94" x2="45.72" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="15" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="15'"/>
<pinref part="U$1" gate="G$1" pin="15"/>
<wire x1="10.16" y1="71.12" x2="27.94" y2="71.12" width="0.1524" layer="91"/>
<wire x1="27.94" y1="71.12" x2="33.02" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="16" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="16'"/>
<pinref part="U$1" gate="G$1" pin="16"/>
<wire x1="10.16" y1="73.66" x2="27.94" y2="73.66" width="0.1524" layer="91"/>
<wire x1="27.94" y1="73.66" x2="33.02" y2="73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD0"/>
<wire x1="50.8" y1="2.54" x2="45.72" y2="2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="18"/>
<pinref part="U$1" gate="G$1" pin="18'"/>
<wire x1="35.56" y1="81.28" x2="35.56" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="19"/>
<pinref part="U$1" gate="G$1" pin="19'"/>
<wire x1="38.1" y1="81.28" x2="38.1" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="22" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="22"/>
<pinref part="U$1" gate="G$1" pin="22'"/>
<wire x1="45.72" y1="81.28" x2="45.72" y2="99.06" width="0.1524" layer="91"/>
<wire x1="45.72" y1="81.28" x2="45.72" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD6"/>
<wire x1="101.6" y1="-10.16" x2="106.68" y2="-10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="23"/>
<pinref part="U$1" gate="G$1" pin="23'"/>
<wire x1="48.26" y1="81.28" x2="48.26" y2="99.06" width="0.1524" layer="91"/>
<wire x1="48.26" y1="81.28" x2="48.26" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="24" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="24"/>
<pinref part="U$1" gate="G$1" pin="24'"/>
<wire x1="50.8" y1="81.28" x2="50.8" y2="99.06" width="0.1524" layer="91"/>
<wire x1="50.8" y1="81.28" x2="50.8" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD7"/>
<wire x1="101.6" y1="-12.7" x2="106.68" y2="-12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="25" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="25"/>
<pinref part="U$1" gate="G$1" pin="25'"/>
<wire x1="53.34" y1="81.28" x2="53.34" y2="99.06" width="0.1524" layer="91"/>
<wire x1="53.34" y1="81.28" x2="53.34" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PA3"/>
<wire x1="101.6" y1="12.7" x2="106.68" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="26" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="26"/>
<pinref part="U$1" gate="G$1" pin="26'"/>
<wire x1="55.88" y1="81.28" x2="55.88" y2="99.06" width="0.1524" layer="91"/>
<wire x1="55.88" y1="81.28" x2="55.88" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PA2"/>
<wire x1="101.6" y1="10.16" x2="106.68" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="27" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="27"/>
<pinref part="U$1" gate="G$1" pin="27'"/>
<wire x1="58.42" y1="81.28" x2="58.42" y2="99.06" width="0.1524" layer="91"/>
<wire x1="58.42" y1="81.28" x2="58.42" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PA4"/>
<wire x1="101.6" y1="15.24" x2="106.68" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="28" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="28"/>
<pinref part="U$1" gate="G$1" pin="28'"/>
<wire x1="60.96" y1="81.28" x2="60.96" y2="99.06" width="0.1524" layer="91"/>
<wire x1="60.96" y1="81.28" x2="60.96" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PA5"/>
<wire x1="50.8" y1="15.24" x2="45.72" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="29"/>
<pinref part="U$1" gate="G$1" pin="29'"/>
<wire x1="63.5" y1="81.28" x2="63.5" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="30" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="30"/>
<pinref part="U$1" gate="G$1" pin="30'"/>
<wire x1="66.04" y1="81.28" x2="66.04" y2="99.06" width="0.1524" layer="91"/>
<wire x1="66.04" y1="81.28" x2="66.04" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE1"/>
<wire x1="50.8" y1="-7.62" x2="45.72" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="31" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="31"/>
<pinref part="U$1" gate="G$1" pin="31'"/>
<wire x1="68.58" y1="81.28" x2="68.58" y2="99.06" width="0.1524" layer="91"/>
<wire x1="68.58" y1="81.28" x2="68.58" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE2"/>
<wire x1="50.8" y1="-10.16" x2="45.72" y2="-10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="32" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="32"/>
<pinref part="U$1" gate="G$1" pin="32'"/>
<wire x1="71.12" y1="81.28" x2="71.12" y2="99.06" width="0.1524" layer="91"/>
<wire x1="71.12" y1="81.28" x2="71.12" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE3"/>
<wire x1="50.8" y1="-12.7" x2="45.72" y2="-12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="33"/>
<pinref part="U$1" gate="G$1" pin="33'"/>
<wire x1="73.66" y1="81.28" x2="73.66" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="34"/>
<pinref part="U$1" gate="G$1" pin="34'"/>
<wire x1="76.2" y1="81.28" x2="76.2" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="36" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="36"/>
<pinref part="U$1" gate="G$1" pin="36'"/>
<wire x1="81.28" y1="81.28" x2="81.28" y2="99.06" width="0.1524" layer="91"/>
<wire x1="81.28" y1="81.28" x2="81.28" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="37" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="37"/>
<pinref part="U$1" gate="G$1" pin="37'"/>
<wire x1="83.82" y1="81.28" x2="83.82" y2="99.06" width="0.1524" layer="91"/>
<wire x1="83.82" y1="81.28" x2="83.82" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="38" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="38"/>
<pinref part="U$1" gate="G$1" pin="38'"/>
<wire x1="86.36" y1="81.28" x2="86.36" y2="99.06" width="0.1524" layer="91"/>
<wire x1="86.36" y1="81.28" x2="86.36" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="39" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="39"/>
<pinref part="U$1" gate="G$1" pin="39'"/>
<wire x1="88.9" y1="81.28" x2="88.9" y2="99.06" width="0.1524" layer="91"/>
<wire x1="88.9" y1="81.28" x2="88.9" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="40"/>
<pinref part="U$1" gate="G$1" pin="40'"/>
<wire x1="91.44" y1="81.28" x2="91.44" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="41" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="41"/>
<pinref part="U$1" gate="G$1" pin="41'"/>
<wire x1="93.98" y1="81.28" x2="93.98" y2="99.06" width="0.1524" layer="91"/>
<wire x1="93.98" y1="81.28" x2="93.98" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD2"/>
<wire x1="50.8" y1="-2.54" x2="45.72" y2="-2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="42" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="42"/>
<pinref part="U$1" gate="G$1" pin="42'"/>
<wire x1="96.52" y1="81.28" x2="96.52" y2="99.06" width="0.1524" layer="91"/>
<wire x1="96.52" y1="81.28" x2="96.52" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD3"/>
<wire x1="50.8" y1="-5.08" x2="45.72" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="43" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="43"/>
<pinref part="U$1" gate="G$1" pin="43'"/>
<wire x1="99.06" y1="81.28" x2="99.06" y2="99.06" width="0.1524" layer="91"/>
<wire x1="99.06" y1="81.28" x2="99.06" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PD1"/>
<wire x1="50.8" y1="0" x2="45.72" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="44" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="44"/>
<pinref part="U$1" gate="G$1" pin="44'"/>
<wire x1="101.6" y1="81.28" x2="101.6" y2="99.06" width="0.1524" layer="91"/>
<wire x1="101.6" y1="81.28" x2="101.6" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="45" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="45"/>
<pinref part="U$1" gate="G$1" pin="45'"/>
<wire x1="104.14" y1="81.28" x2="104.14" y2="99.06" width="0.1524" layer="91"/>
<wire x1="104.14" y1="81.28" x2="104.14" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE4"/>
<wire x1="50.8" y1="22.86" x2="45.72" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="46" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="46"/>
<pinref part="U$1" gate="G$1" pin="46'"/>
<wire x1="106.68" y1="81.28" x2="106.68" y2="99.06" width="0.1524" layer="91"/>
<wire x1="106.68" y1="81.28" x2="106.68" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE5"/>
<wire x1="50.8" y1="20.32" x2="45.72" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="47"/>
<pinref part="U$1" gate="G$1" pin="47'"/>
<wire x1="109.22" y1="81.28" x2="109.22" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="48"/>
<pinref part="U$1" gate="G$1" pin="48'"/>
<wire x1="111.76" y1="81.28" x2="111.76" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="49"/>
<pinref part="U$1" gate="G$1" pin="49'"/>
<wire x1="114.3" y1="81.28" x2="114.3" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="50" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="50"/>
<pinref part="U$1" gate="G$1" pin="50'"/>
<wire x1="116.84" y1="81.28" x2="116.84" y2="99.06" width="0.1524" layer="91"/>
<wire x1="116.84" y1="81.28" x2="116.84" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PF2"/>
<wire x1="101.6" y1="7.62" x2="106.68" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="51" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="51"/>
<pinref part="U$1" gate="G$1" pin="51'"/>
<wire x1="119.38" y1="81.28" x2="119.38" y2="99.06" width="0.1524" layer="91"/>
<wire x1="119.38" y1="81.28" x2="119.38" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PF3"/>
<wire x1="101.6" y1="5.08" x2="106.68" y2="5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="52" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="52"/>
<pinref part="U$1" gate="G$1" pin="52'"/>
<wire x1="121.92" y1="81.28" x2="121.92" y2="99.06" width="0.1524" layer="91"/>
<wire x1="121.92" y1="81.28" x2="121.92" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PB3"/>
<wire x1="101.6" y1="2.54" x2="106.68" y2="2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="53" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="53"/>
<pinref part="U$1" gate="G$1" pin="53'"/>
<wire x1="124.46" y1="81.28" x2="124.46" y2="99.06" width="0.1524" layer="91"/>
<wire x1="124.46" y1="81.28" x2="124.46" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PC4"/>
<wire x1="101.6" y1="0" x2="106.68" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="54" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="54"/>
<pinref part="U$1" gate="G$1" pin="54'"/>
<wire x1="127" y1="81.28" x2="127" y2="99.06" width="0.1524" layer="91"/>
<wire x1="127" y1="81.28" x2="127" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PC5"/>
<wire x1="101.6" y1="-2.54" x2="106.68" y2="-2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="55" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="55"/>
<pinref part="U$1" gate="G$1" pin="55'"/>
<wire x1="129.54" y1="81.28" x2="129.54" y2="99.06" width="0.1524" layer="91"/>
<wire x1="129.54" y1="81.28" x2="129.54" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PC6"/>
<wire x1="101.6" y1="-5.08" x2="106.68" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="61" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="61"/>
<pinref part="U$1" gate="G$1" pin="61'"/>
<wire x1="134.62" y1="63.5" x2="152.4" y2="63.5" width="0.1524" layer="91"/>
<wire x1="134.62" y1="63.5" x2="129.54" y2="63.5" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PB2"/>
<wire x1="101.6" y1="30.48" x2="106.68" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="62" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="62"/>
<pinref part="U$1" gate="G$1" pin="62'"/>
<wire x1="134.62" y1="60.96" x2="152.4" y2="60.96" width="0.1524" layer="91"/>
<wire x1="134.62" y1="60.96" x2="129.54" y2="60.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PF0"/>
<wire x1="101.6" y1="25.4" x2="106.68" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$50" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="63"/>
<pinref part="U$1" gate="G$1" pin="63'"/>
<wire x1="134.62" y1="58.42" x2="152.4" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$51" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="64"/>
<pinref part="U$1" gate="G$1" pin="64'"/>
<wire x1="134.62" y1="55.88" x2="152.4" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="65"/>
<pinref part="U$1" gate="G$1" pin="65'"/>
<wire x1="134.62" y1="53.34" x2="152.4" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="66"/>
<pinref part="U$1" gate="G$1" pin="66'"/>
<wire x1="134.62" y1="50.8" x2="152.4" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="67"/>
<pinref part="U$1" gate="G$1" pin="67'"/>
<wire x1="134.62" y1="48.26" x2="152.4" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$55" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="68"/>
<pinref part="U$1" gate="G$1" pin="68'"/>
<wire x1="134.62" y1="45.72" x2="152.4" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="69" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="69"/>
<pinref part="U$1" gate="G$1" pin="69'"/>
<wire x1="134.62" y1="43.18" x2="152.4" y2="43.18" width="0.1524" layer="91"/>
<wire x1="134.62" y1="43.18" x2="129.54" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="70" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="70"/>
<pinref part="U$1" gate="G$1" pin="70'"/>
<wire x1="134.62" y1="40.64" x2="152.4" y2="40.64" width="0.1524" layer="91"/>
<wire x1="134.62" y1="40.64" x2="129.54" y2="40.64" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PE0"/>
<wire x1="101.6" y1="27.94" x2="106.68" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="71" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="71"/>
<pinref part="U$1" gate="G$1" pin="71'"/>
<wire x1="134.62" y1="38.1" x2="152.4" y2="38.1" width="0.1524" layer="91"/>
<wire x1="134.62" y1="38.1" x2="129.54" y2="38.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PF4"/>
<wire x1="101.6" y1="-15.24" x2="106.68" y2="-15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$59" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="73"/>
<pinref part="U$1" gate="G$1" pin="73'"/>
<wire x1="134.62" y1="33.02" x2="152.4" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$60" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="74"/>
<pinref part="U$1" gate="G$1" pin="74'"/>
<wire x1="134.62" y1="30.48" x2="152.4" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="11" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PB4"/>
<wire x1="50.8" y1="17.78" x2="45.72" y2="17.78" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="11'"/>
<pinref part="U$1" gate="G$1" pin="11"/>
<wire x1="10.16" y1="60.96" x2="27.94" y2="60.96" width="0.1524" layer="91"/>
<wire x1="27.94" y1="60.96" x2="33.02" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="3.3V"/>
<wire x1="50.8" y1="33.02" x2="45.72" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$67" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PA6"/>
<wire x1="50.8" y1="12.7" x2="45.72" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$68" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PA7"/>
<wire x1="50.8" y1="10.16" x2="45.72" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$69" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VBUS"/>
<wire x1="50.8" y1="7.62" x2="45.72" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="GND"/>
<wire x1="50.8" y1="5.08" x2="45.72" y2="5.08" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND'"/>
<wire x1="101.6" y1="33.02" x2="106.68" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$78" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PF1"/>
<wire x1="50.8" y1="-15.24" x2="45.72" y2="-15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$83" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="RST"/>
<wire x1="101.6" y1="22.86" x2="106.68" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$84" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PB7"/>
<wire x1="101.6" y1="20.32" x2="106.68" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$85" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PB6"/>
<wire x1="101.6" y1="17.78" x2="106.68" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$95" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PC7"/>
<wire x1="101.6" y1="-7.62" x2="106.68" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
