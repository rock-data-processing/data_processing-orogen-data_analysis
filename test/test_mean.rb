require "orocos"
Orocos.initialize

Orocos.run "data_analysis::MeanTask" => "mean" do
    task = Orocos::TaskContext.get "mean"
    task.window_size = Float::INFINITY
    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.mean.reader

    while true
        input_data = Types.base.VectorXd.from_a [Random.rand,2*Random.rand,3*Random.rand]
        writer.write input_data
        sleep 0.1
        sample = reader.read
        if sample
            puts "Input data:    " + input_data.to_s
            puts "Mean:          " + sample.to_s
            puts "................................."
        end
    end
end
