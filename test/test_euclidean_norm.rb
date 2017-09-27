require "orocos"
Orocos.initialize

Orocos.run "data_analysis::EuclideanNorm" => "norm" do
    task = Orocos::TaskContext.get "norm"
    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.norm.reader

    while true
        input_data = Types.base.VectorXd.from_a [rand(-1.0..1.0),rand(-1.0..1.0),rand(-1.0..1.0)]
        writer.write input_data
        sample = reader.read

        puts "norm(" + input_data.to_a.to_s + ") = " + sample.to_s if sample

        sleep 0.1
    end
end
