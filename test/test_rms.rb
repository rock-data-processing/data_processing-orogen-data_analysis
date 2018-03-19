require "orocos"
Orocos.initialize
Orocos.conf.load_dir("config")

Orocos.run "data_analysis::RMSTask" => "rms" do
    task = Orocos::TaskContext.get "rms"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer_rbs = task.rbs.writer
    input_rbs  = Types.base.samples.RigidBodyState.new
    reader_rbs = task.rms_rbs.reader

    writer_joints = task.joints.writer
    input_joints = Types.base.samples.Joints.new
    input_joints.elements = [Types.base.JointState.new]*2
    reader_joints = task.rms_joints.reader

    while true
        input_rbs.position = Types.base.Vector3d.new(1 + 0.1*Random.rand - 0.05, 2 + 0.1*Random.rand - 0.05, 3 + 0.1*Random.rand - 0.05)
        input_joints.elements[0].position = 4.0 + 0.1*Random.rand - 0.05
        input_joints.elements[1].position = 5.0 + 0.1*Random.rand - 0.05

        input_rbs.time = Types.base.Time.now
        writer_rbs.write input_rbs
        input_joints.time = Types.base.Time.now
        writer_joints.write input_joints

        sleep 0.1
        sample_rbs = reader_rbs.read
        if sample_rbs
            puts "RBS  port:"
            puts "Input data:    " + input_rbs.position.to_a.to_s
            puts "RMS:           " + sample_rbs.to_s
            puts
        end
        sample_joints = reader_joints.read
        if sample_joints
            puts "Joints port:"
            puts "Input data:    [" + input_joints.elements[0].position.to_s + " " + input_joints.elements[1].position.to_s + "]"
            puts "RMS:           " + sample_joints.to_s
            puts "................................."
        end
    end
end
