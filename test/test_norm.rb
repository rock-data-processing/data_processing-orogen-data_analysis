require "orocos"
Orocos.initialize

Orocos.run "data_analysis::NormTask" => "norm" do
    task = Orocos::TaskContext.get "norm"
    task.p = 2
    task.configure
    task.start

    writer = task.input_data.writer
    input_data = Types.base.VectorXd.from_a [-1,2,-3]
    reader = task.norm.reader

    while true
        writer.write input_data
        sleep 0.1
        sample = reader.read
        if sample
            puts "Input data:    " + input_data.to_s
            puts "Norm:          " + sample.to_s
            puts "................................."
        end
    end
end
