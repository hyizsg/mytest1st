#!/usr/bin/env python
# -*- coding: utf-8 -*-

import xlrd,sys,string
# from pyExcelerator import*

if len(sys.argv)<4:
    print 'usage:txt-excel-Converter -t2e [-e2t] srcFile destFile'
    sys.exit()

direction=sys.argv[1]
fin=sys.argv[2];
fout=sys.argv[3];
print sys.argv[0]+' '+direction+' '+fin+' '+fout


def txt2excel():
    #h=25
    #fnt=Font()
    #fnt.height=17
    #style=XFStyle()
    #style.font=fnt
    f=file(fin)
    wb=Workbook()
    ws=wb.add_sheet('localization')
    #ws.col(0).width = 100
    #ws.col(1).width = 20
    #ws.col(2).width = 300
    #ws.row(0).height = h
    ws.write(0,0,'key')
    ws.write(0,1,'=')
    ws.write(0,2,'value')
    row=1
    while True:
        line=f.readline();
        if len(line)<1:
            break;
        #print line
        l=string.split(line, ' = ')
        cols=len(l)
        #ws.row(row).height = h
        if cols==1:
            ws.write(row,0,l[0])
        elif cols==2:
            ws.write(row,0,l[0])
            ws.write(row,1,' = ')
            ws.write(row,2,unicode(l[1],'utf-8'))
        #ws.write(row,0,line)
        row=row+1
    wb.save(fout)

def excel2txt():
    wb=xlrd.open_workbook(fin)
    sh=wb.sheet_by_index(0)
    f=file(fout, 'w')
    for row in range(1,sh.nrows):
        l=[];
        for col in range(sh.ncols):
            s=sh.cell(row,col).value.encode('utf-8')
            s=string.strip(s)
            if col==0:
                l.append(s)
            elif col==2:
                if len(s)>0:
                    l.append(s)
            else:
                if len(s)>0:
                    l.append(s)
        line=string.join(l)
        #print line
        if len(line) > 0:
            f.write(line)
        #else:
        #    f.write('\n')
        f.write('\n')
    f.close();

def txt2excel1():
    f1=file('./zh_cn.lproj/Localizable.strings')
    f2=file('./en.lproj/Localizable.strings')
    wb=Workbook()
    ws=wb.add_sheet('localization')
    ws.write(0,0,'key')
    ws.write(0,1,'simplified chinese')
    ws.write(0,2,'english')
    row=1
    while True:
        key1=u''
        value1=u''
        key2=u''
        value2=u''
        line=f1.readline()
        if len(line)<1:
            print 'read ./zh_cn.lproj/Localizable.strings over'
            break
        l=string.split(line,' = ')
        cols=len(l)
        if cols>0:
            s=l[0]
            s=string.strip(s);
            if s[:1]=='"':
                s=s[1:len(s)-1]
            key1=unicode(s,'utf-8')
        if cols>1:
            s=l[1]
            s=string.strip(s);
            if s[:1]=='"':
                s=s[1:len(s)-2]
            value1=unicode(s,'utf-8')
        line=f2.readline()
        if len(line)<1:
            print 'read ./en.lproj/Localizable.strings over'
            break
        l=string.split(line,' = ')
        cols=len(l)
        if cols>0:
            s=l[0]
            s=string.strip(s);
            if s[:1]=='"':
                s=s[1:len(s)-1]
            key2=unicode(s,'utf-8')
        if cols>1:
            s=l[1]
            s=string.strip(s);
            if s[:1]=='"':
                s=s[1:len(s)-2]
            value2=unicode(s,'utf-8')
        if key1==key2:
            ws.write(row,0,key1)
            if len(value1)>1:
                ws.write(row,1,value1)
                ws.write(row,2,value2)
        else:
            print 'read the key is not same, please revise the original file key of Localizable.strings';
            break;
        row=row+1
    wb.save(fout)
    
def excel2txt1():
    wb=xlrd.open_workbook(fin)
    sh=wb.sheet_by_index(0)
    f1=file(fout+'/zh_cn.lproj/Localizable.strings', 'w')
    f2=file(fout+'/en.lproj/Localizable.strings', 'w')
    for row in range(0,sh.nrows):
        l=[];
        for col in range(sh.ncols):
            if sh.cell(row,col).ctype=='text':
                s=sh.cell(row,col).value.encode('utf-8')
            elif sh.cell(row,col).ctype=='number':
                f=sh.cell(row,col).value
                s=unicode(int(f)).encode('utf-8')
            else:
                s=unicode(sh.cell(row,col).value).encode('utf-8')
            s=string.strip(s)
            l.append(s)
            
        if len(l[0])>0:
            if l[0][:2]=='//':
                if len(l[1])<1:
                    f1.write(l[0])
                else:
                    f1.write(l[0]+' = "'+l[1]+'";')
                if len(l[2])<1:
                    f2.write(l[0])
                else:
                    f2.write(l[0]+' = "'+l[2]+'";')
            else:
                f1.write('"'+l[0]+'" = "'+l[1]+'";')
                f2.write('"'+l[0]+'" = "'+l[2]+'";')
        f1.write('\n')
        f2.write('\n')
    f1.close();
    f2.close();
    
if direction=='-t2e':
    print 'txt to excel'
    txt2excel1()
elif direction=='-e2t':
    print 'excel to txt'
    excel2txt1()
else:
    print 'invalid param'
