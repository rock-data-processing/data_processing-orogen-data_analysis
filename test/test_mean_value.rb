require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Mean" => "mean" do
    task = Orocos::TaskContext.get "mean"
    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.mean.reader

    input_data = Types.base.VectorXd.from_a [-1,2,-3]

    while true
        writer.write input_data
        sample = reader.read

        puts "mean(" + input_data.to_a.to_s + ") = " + sample.to_s if sample

        sleep 0.1
    end
end
