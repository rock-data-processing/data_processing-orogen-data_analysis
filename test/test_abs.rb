require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Abs" => "abs" do
    task = Orocos::TaskContext.get "abs"
    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.abs.reader

    input_data = Types.base.VectorXd.from_a [-1,2,-3]

    while true
        writer.write input_data
        sample = reader.read

        puts "abs(" + input_data.to_a.to_s + ") = " + sample.to_a.to_s if sample

        sleep 0.1
    end
end
