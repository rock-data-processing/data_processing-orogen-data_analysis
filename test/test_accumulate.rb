require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Accumulate" => "acc" do
    task = Orocos::TaskContext.get "acc"
    task.window_size = 10
    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.output_data.reader

    input_data = 0
    while true
        writer.write input_data
        sample = nil
        while !sample
            sample = reader.read_new
        end
        puts "Input data: " + input_data.to_s
        puts "Output data: " + sample.to_s
        puts "................................."
        input_data += 1
        sleep 0.2
    end
end
