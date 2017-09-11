require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Sum" => "sum" do
    task = Orocos::TaskContext.get "sum"
    task.configure
    task.start

    writer_one = task.summand_one.writer
    writer_two = task.summand_two.writer
    reader     = task.sum.reader

    summand_one = Types.base.VectorXd.from_a [1,2,3]
    summand_two = Types.base.VectorXd.from_a [4,5,6]

    while true
        writer_one.write summand_one
        writer_two.write summand_two

        sample = reader.read

        puts summand_one.to_a.to_s + " + " + summand_two.to_a.to_s + " = " + sample.to_a.to_s if sample

        sleep 0.1
    end
end
