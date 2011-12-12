#!/usr/bin/env python
#
# name:      python/NPCCM.py
# author:    CAO Ya-qiang
# license:   GPL
# created:   2011 Dec 12
# modified:  2011 Dec 12
#
#--coding:utf-8--

import time
import argparse
from multiprocessing import Pool
import numpy as np


def  read_data_file(path):
        data_file=open(path)
        try:
                variable_names=data_file.readline().split()
                colomn_number=len(variable_names)
                original_data_dict_list=[]
                for line in data_file.readlines():
                       line=line.split()
                       #convert string to float and ensure there is no meanless value
                       try: 
                               line_data=map(float,line[1:])
                               if len(line_data)==colomn_number-1:
                                   original_line_array=np.array(line_data)
                                   fen_mu=np.sqrt(len(original_line_array)*np.sum(np.square(original_line_array))-np.square(np.sum(original_line_array))) 
                                   if fen_mu!=0:
                                      gen_dict={'ID':line[0],'Variable':tuple(line_data)}
                                      original_data_dict_list.append(gen_dict)
                       except ValueError:
                               continue
        except IOError: 
                 print 'cannot open: ',path                                
        finally:
                 data_file.close()

        multiple_two_dimension_dict_tuple_list=[]
        row=len(original_data_dict_list)
        
        for i in range(0,row-1):
               x=original_data_dict_list[i]
               for j in range(i+1,row):
                      y=original_data_dict_list[j]
                      tuple_dict=(x,y)
                      multiple_two_dimension_dict_tuple_list.append(tuple_dict)

                
        return multiple_two_dimension_dict_tuple_list
        
             


def  Pcc(two_dimension_dict_tuple):
         global CONTER
         global II
         global ONE
         CONTER=CONTER+1
         if CONTER==II*ONE:
            print  'again',10,'% is done'
            II=II+1
         
         x=np.array(two_dimension_dict_tuple[0]['Variable'])
         y=np.array(two_dimension_dict_tuple[1]['Variable'])
         colomn=len(x)               
         fen_zi=colomn*np.sum(x*y)-np.sum(x)*np.sum(y)
         fen_mu=np.sqrt(colomn*np.sum(np.square(x))-np.square(np.sum(x)))*np.sqrt(colomn*np.sum(np.square(y))-np.square(np.sum(y)))
         return fen_zi/fen_mu
                      



def  sPcc(multiple_two_dimension_dict_tuple_list):
        result_data_list=map(Pcc,multiple_two_dimension_dict_tuple_list)
        return result_data_list



def mPcc(multiple_two_dimension_dict_tuple_list,process_number):
        pool=Pool(processes=process_number)
        result_data_list=pool.map(Pcc,multiple_two_dimension_dict_tuple_list) 
        return result_data_list


             
def   write_data_file(output_file_path,result_data_list,multiple_two_dimension_dict_tuple_list):
         result_len=len(result_data_list)
         result_dict_list=[]
         for i in range(result_len):
            input_dict=multiple_two_dimension_dict_tuple_list[i]
            ouput_dict={'gen1':input_dict[0]['ID'],'gen2':input_dict[1]['ID'],'PCC':result_data_list[i]}
            result_dict_list.append(ouput_dict)
        
         output_file_object= open(output_file_path,'w')
         for rdl in result_dict_list:
             newline=rdl['gen1']+'\t'+rdl['gen2']+'\t'+str(rdl['PCC'])+'\n'
             output_file_object.write(newline)               
         output_file_object.close( )





def  main_process(input_file_path,ouput_file_path,process_number,mode):
        multiple_two_dimension_dict_tuple_list=read_data_file(input_file_path)
        TOTAL_len=len(multiple_two_dimension_dict_tuple_list)
        global ONE
        ONE=int(TOTAL_len/10)
        global CONTER
        CONTER=0   
        global II
        II=1
        if mode==1:
           result_data_list=sPcc(multiple_two_dimension_dict_tuple_list) 
        if mode==2:
           result_data_list=mPcc(multiple_two_dimension_dict_tuple_list,process_number)
        write_data_file(output_file_path,result_data_list,multiple_two_dimension_dict_tuple_list)

        
        
#The main funciton
if __name__=='__main__':
   #Caculate the time used for the programme
   start_time=time.clock()
   
   #The  command line parse
   parser = argparse.ArgumentParser(description='The programe is going to caculate the Pearson Correlation Coefficient of  the related genes in the data file')
   parser.add_argument('-f', '--file', dest='fn', help='input file name.', default='data.txt')
   parser.add_argument('-o', '--output', dest='fnOut', help='output file name, default is output.txt', default='output.txt')
   parser.add_argument('-p','--Process Number',type=int,default=2,dest='process_number',help='input the process number need for the programme, default is 2')
   parser.add_argument('-m','--caculate mode',type=int,default=2,dest='mode',help='chose the mode for the programme:1 for personal computer;2 for severs.Default is 2.')
   op= parser.parse_args()
   input_file_path=str(op.fn)
   output_file_path=str(op.fnOut)
   process_number=op.process_number
   mode=op.mode

   main_process(input_file_path,output_file_path,process_number,mode)
   
   
   elapsed=time.clock()-start_time
   print "The process is done"
   print "Time used:",elapsed

