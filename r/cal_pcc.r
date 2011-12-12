#cal PCC using R
a=read.table('GSE5430_flybase.for_pcc',sep="\t",header=F)

cal_cor<-function(df){
    A<-t(df[,2:length(df[1,])])
    colnames(A)<-df[,1]
    CovA <- cor(A,method="pearson")
    RCovA <- round(CovA,4)
    RCovA
}
cor_a=cal_cor(a)
write.table(cor_a[,c("44505","34358")],file='GSE5430_flybase.cor',row.names=T,col.names=T,quote =F,sep="\t")

# another case
a=c(1,2,3,4,5)
b=c(5,5,6,7,8)
cor(a, b, method="pearson")
# 0.970145
