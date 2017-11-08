package example

import org.apache.spark.{SparkContext, SparkConf}
import org.apache.spark.rdd.RDD
import org.apache.spark.mllib.fpm.FPGrowth

object Hello extends Greeting with App {
  println(greeting)

  val conf = new SparkConf().setAppName("Ex1_SimpleRDD").setMaster("local[4]")
  val sc = new SparkContext(conf)


  val data = sc.textFile("data.csv")
  val transactions: RDD[Array[String]] = data.map(s => s.trim.split(", "))

  val fpg = new FPGrowth().setMinSupport(0.2).setNumPartitions(10)
  val model = fpg.run(transactions)

  model.freqItemsets.collect().foreach { itemset => println(itemset.items.mkString("[", ",", "]") + ", " + itemset.freq) }

  val minConfidence = 0.8
  model.generateAssociationRules(minConfidence).collect().foreach { rule => println(rule.antecedent.mkString("[", ",", "]") + " => " + rule.consequent .mkString("[", ",", "]") + ", " + rule.confidence) }
  sc.stop()
}

trait Greeting {
  lazy val greeting: String = "hello"
}
