require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::WeightedSumTask" => "weighted_sum" do
    task = Orocos::TaskContext.get "weighted_sum"
    task.weights = Types.base.VectorXd.from_a [1,2]
    task.configure
    task.start

    writer_0 = task.summand_0.writer
    writer_1 = task.summand_1.writer

    writer_2 = task.vect_summand_0.writer
    writer_3 = task.vect_summand_1.writer

    input_0 = 1
    input_1 = 2
    input_2 = Types.base.VectorXd.from_a [1,2]
    input_3 = Types.base.VectorXd.from_a [3,4]

    reader_0 = task.weighted_sum.reader
    reader_1 = task.weighted_sum_vect.reader

    puts "Press Ctrl-C to exit"

    while true
        writer_0.write input_0
        writer_1.write input_1
        sleep 1
        sample = reader_0.read
        if sample
            puts "Input data 1:    " + input_0.to_s
            puts "Input data 2:    " + input_1.to_s
            puts "Weights:         " + task.weights.to_s
            puts "Output data:     " + sample.to_s
            puts
        end

        writer_2.write input_2
        writer_3.write input_3
        sleep 0.5
        sample = reader_1.read
        if sample
            puts "Input vector data 1:    " + input_2.to_s
            puts "Input vector data 2:    " + input_3.to_s
            puts "Weights:         " + task.weights.to_s
            puts "Output data:     " + sample.to_s
            puts "................................."
        end
        sleep 1
    end
end
