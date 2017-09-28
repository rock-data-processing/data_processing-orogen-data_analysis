require "orocos"
Orocos.initialize

Orocos.run "data_analysis::WeightedSum" => "weighted_sum" do
    task = Orocos::TaskContext.get "weighted_sum"
    weights = [0.5,0.5]
    task.weights = Types.base.VectorXd.from_a weights
    task.configure
    task.start

    writer_0 = task.input_0.writer
    writer_1 = task.input_1.writer
    reader = task.weighted_sum.reader

    while true
        input_data = [rand(), rand()]
        writer_0.write input_data[0]
        writer_1.write input_data[1]
        sleep 1
        sample = reader.read
        if sample
            puts "Input data:      " + input_data.to_s
            puts "Weights:         " + weights.to_s
            puts "Expected output: " + (weights[0] * input_data[0] + weights[1] * input_data[1]).to_s
            puts "Output data:     " + sample.to_s
            puts "................................."
        end
    end
end
